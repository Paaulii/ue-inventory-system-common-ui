// Copyright Paulina Hałatek, All Rights Reserved.


#include "Player/Components/Inventory/INV_InventoryComponent.h"

#include "Data/INV_InventoryDataAsset.h"
#include "Data/INV_ModalPromptTexts.h"
#include "Data/Types/INV_ItemActionType.h"
#include "Data/Types/INV_ItemSaveDataTypes.h"
#include "Items/INV_Item.h"
#include "Items/INV_SkeletalMeshItem.h"
#include "Items/INV_StaticMeshItem.h"
#include "Kismet/GameplayStatics.h"
#include "Player/INV_PlayerController.h"
#include "Player/Data/INV_InventorySaveData.h"
#include "UI/UIS_CommonUIExtensions.h"
#include "UI/UIS_CommonUILayerTags.h"
#include "UI/UIS_PrimaryGameLayout.h"
#include "UI/Widgets/INV_InventoryScreen.h"

void UINV_InventoryComponent::ToggleInventory()
{
	SetInventoryVisible(!bInventoryMenuOpen);
}

void UINV_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	OwningController = Cast<AINV_PlayerController>(GetOwner());
}

void UINV_InventoryComponent::DropItem(const FINV_ItemIdentification& ItemId, const int16 Amount)
{
	if (OwningController == nullptr)
	{
		return;
	}
	
	TryUnequipItem(ItemId);
	
	if (!DecreaseItemQuantity(ItemId, Amount))
	{
		return;
	}
	
	FINV_ItemAssetDefinition* ItemAssetDef = GetItemAssetDefinition(ItemId);
	
	if (!ItemAssetDef->SkeletalMesh && !ItemAssetDef->StaticMesh)
	{
		return;
	}
	
	if (UWorld* World = GetWorld() )
	{
		TSubclassOf<AINV_Item> ItemClass = ItemAssetDef->SkeletalMesh ? SkeletalMeshItemClass : StaticMeshItemClass;
		
		float Alpha = FMath::FRand() * PI * 2.0f;
		float Cos = FMath::Cos(Alpha);
		float Sin = FMath::Sin(Alpha);
		float X = Cos * DropItemRadius * FMath::FRand();
		float Y = Sin * DropItemRadius * FMath::FRand();

		FVector RandomPointInRadius = FVector(X, Y, DropItemHeight);
		FVector PlayerLocation = OwningController->GetPawn()->GetActorLocation();
		FVector DropItemLocation = FVector(PlayerLocation.X + RandomPointInRadius.X, PlayerLocation.Y + RandomPointInRadius.Y,  RandomPointInRadius.Z);
		AActor* SpawnedItem = World->SpawnActor(ItemClass, &DropItemLocation);

		if (!SpawnedItem)
		{
			return;
		}
		
		if (AINV_Item* Item = Cast<AINV_Item>(SpawnedItem))
		{
			Item->Initialize(FINV_ItemData(ItemId, Amount));
		}
	}
}

void UINV_InventoryComponent::LoadInventoryData()
{
	UINV_InventorySaveData* LoadGameInstance = Cast<UINV_InventorySaveData>(UGameplayStatics::LoadGameFromSlot("SaveData", 0));

	int32 CurrencyAmount = 0;
	int32 MaxItemsCapacity = DefaultInventoryCapacity;
	
	if (LoadGameInstance)
	{
		CachedPlayerItems = LoadGameInstance->GetInventoryItems();
		EquippedItems = LoadGameInstance->GetEquippedItems();
		CurrencyAmount = LoadGameInstance->GetCurrencyAmount();
		MaxItemsCapacity = LoadGameInstance->GetMaxItemsCapacity();
	}
	else
	{
		UINV_InventorySaveData* InventorySaveData = NewObject<UINV_InventorySaveData>();
		InventorySaveData->SetInventorySaveData(CurrencyAmount,MaxItemsCapacity, CachedPlayerItems, EquippedItems);
		UGameplayStatics::SaveGameToSlot(InventorySaveData, "SaveData", 0);
	}
	
	TArray<FINV_CategoryDisplayData> CategoryDisplayDataArray = TranslatePlayerItemsToDisplayData();

	FINV_InventoryDisplayData InventoryDisplayData = FINV_InventoryDisplayData(
		CurrencyAmount,
		MaxItemsCapacity,
		CategoryDisplayDataArray
	);
	
	CachedInventoryDisplayData = InventoryDisplayData;
	OnInventoryDataParsed.ExecuteIfBound(InventoryDisplayData);

	EquipItems();
}

FINV_ItemAssetDefinition* UINV_InventoryComponent::GetItemAssetDefinition(const FINV_ItemIdentification& ItemId) const
{
	return InventoryDataAsset->GetItemDefinition(ItemId.ItemTag, ItemId.CategoryTag);
}

void UINV_InventoryComponent::EquipItems()
{
	for (FINV_ItemIdentification& ItemToEquip : EquippedItems)
	{
		EquipItem(ItemToEquip);
	}
}

void UINV_InventoryComponent::ConsumeItem(const FINV_ItemIdentification& ItemId, const int16 Amount)
{
	DelegateApplyEffects(ItemId);
	DecreaseItemQuantity(ItemId, Amount);
}

bool UINV_InventoryComponent::DecreaseItemQuantity(const FINV_ItemIdentification& ItemId, const int16 Amount)
{
	FINV_ItemData* CachedItemData = GetCachedItem(ItemId.Id);

	if (!CachedItemData)
	{
		return false;
	}
	
	CachedItemData->Quantity = CachedItemData->Quantity - Amount;

	if (CachedItemData->Quantity <= 0)
	{
		CachedPlayerItems.RemoveAll([ItemId](const FINV_ItemData& CurrentItem)
		{
			return CurrentItem.ItemIdentification.Id == ItemId.Id;
		});
		
		CachedInventoryDisplayData.RemoveItemAt(ItemId.Id);
	}
	else
	{
		UpdateDisplayInventoryDataEntry(*CachedItemData);
	}
	
	SaveInventoryData(CachedPlayerItems);
	if (const FINV_CategoryDisplayData* CategoryDisplayData = CachedInventoryDisplayData.GetCategory(CachedItemData->ItemIdentification.CategoryTag))
	{
		OnCategoryItemsChanged.ExecuteIfBound(*CategoryDisplayData);
		return true;
	}

	return false;
}


void UINV_InventoryComponent::DelegateApplyEffects(const FINV_ItemIdentification& ItemId) const
{
	FINV_ItemAssetDefinition* ItemAssetDef = GetItemAssetDefinition(ItemId);

	if (ItemAssetDef)
	{
		OnDelegateApplyEffect.Broadcast(ItemAssetDef->Effects);
	}
}

int32 UINV_InventoryComponent::GetNextGUID() const
{
	if (CachedPlayerItems.Num() == 0)
	{
		return 0;
	}
	
	int32 HighestUID = 0;
	for (const FINV_ItemData& ItemData : CachedPlayerItems)
	{
		if (ItemData.ItemIdentification.Id > HighestUID)
		{
			HighestUID = ItemData.ItemIdentification.Id;
		}
	}
	
	return HighestUID + 1;
}

FINV_ItemData* UINV_InventoryComponent::GetCachedItem(int16 ItemUID)
{
	for (FINV_ItemData& Item : CachedPlayerItems)
	{
		if (Item.ItemIdentification.Id == ItemUID)
		{
			return &Item;
		}
	}

	return nullptr;
}

TArray<FINV_CategoryDisplayData> UINV_InventoryComponent::TranslatePlayerItemsToDisplayData()
{
	TArray<FINV_CategoryDisplayData> CategoryDisplayDataList;
	
	if (!InventoryDataAsset)
	{
		return CategoryDisplayDataList;
	}
	
	TMap<FGameplayTag, TArray<FINV_ItemDisplayData>> ItemsPerCategory;
	for (int i = 0; i < CachedPlayerItems.Num(); i++ ) {
		FINV_ItemData CachedPlayerItem = CachedPlayerItems[i];
		TOptional<FINV_ItemDisplayData> ItemDisplayData = CreateItemDisplayData(CachedPlayerItem);

		if (!ItemDisplayData.IsSet())
		{
			continue;
		}
		
		TArray<FINV_ItemDisplayData>* ItemList = &ItemsPerCategory.FindOrAdd(CachedPlayerItem.ItemIdentification.CategoryTag);
		
		ItemList->Add(ItemDisplayData.GetValue());
	}

	for (const auto& CurrentCategoryData : InventoryDataAsset->Categories)
	{
		TArray<FINV_ItemDisplayData>* ItemList = &ItemsPerCategory.FindOrAdd(CurrentCategoryData.CategoryTag);
		FINV_CategoryDisplayData NewCategory = FINV_CategoryDisplayData(CurrentCategoryData.CategoryTag, CurrentCategoryData.CategoryName,*ItemList);
		CategoryDisplayDataList.Add(NewCategory);
	}

	return CategoryDisplayDataList;
}

FINV_ItemData* UINV_InventoryComponent::GetCachedItemBy(int16 ItemId)
{
	for (int i = 0; i < CachedPlayerItems.Num(); i++) 
	{
		if (CachedPlayerItems[i].ItemIdentification.Id == ItemId)
		{
			return &CachedPlayerItems[i];
		}
	}

	return nullptr;
}

void UINV_InventoryComponent::SetInventoryVisible(bool bIsVisible)
{
	if (bIsVisible)
	{
		OwningController->SetInputMode(FInputModeGameAndUI());
	}
	else
	{
		OwningController->SetInputMode(FInputModeGameOnly());
	}

	OwningController->SetShowMouseCursor(bIsVisible);

	bInventoryMenuOpen = bIsVisible;

	if (!bIsVisible)
	{
		return;
	}

	RequestShowInventory();
}

void UINV_InventoryComponent::RequestShowInventory()
{
	UCommonActivatableWidget* WidgetToActivate = UUIS_CommonUIExtensions::PushContentToLayer(OwningController->GetLocalPlayer(), UI::Layer::GameMenu, InventoryClass);
	
	if (!bIsBindToInventoryOnDeactivated)
		if (UINV_InventoryScreen* InventoryScreen = Cast<UINV_InventoryScreen>(WidgetToActivate))
		{
			bIsBindToInventoryOnDeactivated = true;
			InventoryScreen->OnDeactivated().AddLambda([this, InventoryScreen]()
			{
				SetInventoryVisible(false);
				InventoryScreen->OnDeactivated().RemoveAll(this);
				bIsBindToInventoryOnDeactivated = false;
			});
		}
}

void UINV_InventoryComponent::SaveInventoryData(const TArray<FINV_ItemData>& DataToSave) const
{
	UINV_InventorySaveData* InventorySaveData = Cast<UINV_InventorySaveData>(UGameplayStatics::LoadGameFromSlot("SaveData", 0));
	if (!InventorySaveData)
	{
		return;
	}
	
	InventorySaveData->SetPlayerItems(DataToSave);
	UGameplayStatics::SaveGameToSlot(InventorySaveData, "SaveData", 0);
}

void UINV_InventoryComponent::SaveEquipPlayerItems(const TArray<FINV_ItemIdentification>& EquippedItemsToSave) const
{
	UINV_InventorySaveData* InventorySaveData = Cast<UINV_InventorySaveData>(UGameplayStatics::LoadGameFromSlot("SaveData", 0));
	if (!InventorySaveData)
	{
		return;
	}
	
	InventorySaveData->SetEquippedItems(EquippedItemsToSave);
	UGameplayStatics::SaveGameToSlot(InventorySaveData, "SaveData", 0);
}

void UINV_InventoryComponent::TryAddItem(const FINV_ItemData& ItemData)
{
	FINV_ItemAssetDefinition* ItemAssetDefinition =  GetItemAssetDefinition(ItemData.ItemIdentification);

	if (!ItemAssetDefinition)
	{
		return;
	}
	
	int ReminderQuantityToAdd = ItemData.Quantity;
	const int MaxQuantity = ItemAssetDefinition->MaxQuantity;

	if (CachedPlayerItems.Num() > 0)
	{
		for (int i = 0 ; i < CachedPlayerItems.Num(); i++)
		{
			FINV_ItemData& CurrentItemData = CachedPlayerItems[i];
			if (CurrentItemData.ItemIdentification.ItemTag != ItemData.ItemIdentification.ItemTag ||
			CurrentItemData.ItemIdentification.CategoryTag != ItemData.ItemIdentification.CategoryTag ||
				CurrentItemData.Quantity >= MaxQuantity)
			{
				continue;
			}
				
			int16 QuantityAfterAddition = CurrentItemData.Quantity + ReminderQuantityToAdd;
			ReminderQuantityToAdd = QuantityAfterAddition - MaxQuantity;

			CurrentItemData.Quantity = FMath::Clamp(QuantityAfterAddition, 0, MaxQuantity);
			UpdateDisplayInventoryDataEntry(CurrentItemData);
		}
	}
	
	int32 NextUID = GetNextGUID();
	while (ReminderQuantityToAdd > 0)
	{
		int16 ItemQuantity = ReminderQuantityToAdd;
		
		if (ReminderQuantityToAdd >= MaxQuantity)
		{
			ItemQuantity = MaxQuantity;
		}
		

		FINV_ItemData NewItemData = FINV_ItemData(FINV_ItemIdentification(NextUID, ItemData.ItemIdentification.ItemTag, ItemData.ItemIdentification.CategoryTag), ItemQuantity);
		CachedPlayerItems.Add(NewItemData);
		UpdateDisplayInventoryDataEntry(NewItemData);
		ReminderQuantityToAdd -= ItemQuantity;
		NextUID++;
	}

	SaveInventoryData(CachedPlayerItems);
	if (const FINV_CategoryDisplayData* CategoryDisplayData = CachedInventoryDisplayData.GetCategory(ItemData.ItemIdentification.CategoryTag))
	{
		OnCategoryItemsChanged.ExecuteIfBound(*CategoryDisplayData);
	}
}

void UINV_InventoryComponent::TryEquipItem(const FINV_ItemIdentification& ItemIdentification)
{
	FINV_ItemAssetDefinition* ItemToEquipAssetDefinition = GetItemAssetDefinition(ItemIdentification);
	int32 ItemToUnequipIndex = EquippedItems.IndexOfByPredicate([this, &ItemToEquipAssetDefinition](const FINV_ItemIdentification& EquippedItemId){
		FINV_ItemAssetDefinition* EquippedItemAssedDefinition =  GetItemAssetDefinition(EquippedItemId);
		
		return ItemToEquipAssetDefinition->EquipType == EquippedItemAssedDefinition->EquipType;
	});
	
	if (ItemToUnequipIndex >= 0)
	{
		UnequipItemAt(ItemToUnequipIndex);
	}
	
	EquippedItems.Add(ItemIdentification);
	EquipItem(ItemIdentification);
	SaveEquipPlayerItems(EquippedItems);
}

void UINV_InventoryComponent::EquipItem(const FINV_ItemIdentification& ItemIdentification) const
{
	FINV_ItemAssetDefinition* ItemToEquipAssetDefinition = GetItemAssetDefinition(ItemIdentification);
	OnItemEquipped.Broadcast(ItemIdentification);
	OnDelegateApplyEffect.Broadcast(ItemToEquipAssetDefinition->Effects);
}

void UINV_InventoryComponent::TryUnequipItem(const FINV_ItemIdentification& ItemIdentification)
{
	int32 ItemToUnequipIndex = EquippedItems.IndexOfByPredicate([this, &ItemIdentification](const FINV_ItemIdentification& EquippedItem){
		return EquippedItem.Id == ItemIdentification.Id;
	});
	
	if (ItemToUnequipIndex >= 0)
	{
		UnequipItemAt(ItemToUnequipIndex);
		SaveEquipPlayerItems(EquippedItems);
	}
}

void UINV_InventoryComponent::UnequipItemAt(const int32 IndexToUnequip)
{
	if (IndexToUnequip > EquippedItems.Num())
	{
		return;
	}

	const FINV_ItemIdentification ItemId = EquippedItems[IndexToUnequip];
	FINV_ItemAssetDefinition* ItemToUnequipAssetDefinition = GetItemAssetDefinition(ItemId);
	OnItemUnequipped.Broadcast(ItemId);
	EquippedItems.RemoveAt(IndexToUnequip);
	OnDelegateRevokeEffect.Broadcast(ItemToUnequipAssetDefinition->Effects);
}

void UINV_InventoryComponent::SellItem(const FINV_ItemIdentification& ItemId, const int16 Amount)
{
	TryUnequipItem(ItemId);
	
	if (!DecreaseItemQuantity(ItemId, Amount))
	{
		return;
	}
	
	if (FINV_ItemAssetDefinition* ItemDefinition = GetItemAssetDefinition(ItemId))
	{
		int SellValue = ItemDefinition->CurrencyValue * Amount;
		
		UINV_InventorySaveData* InventorySaveData = Cast<UINV_InventorySaveData>(UGameplayStatics::LoadGameFromSlot("SaveData", 0));
		if (!InventorySaveData)
		{
			return;
		}

		CachedInventoryDisplayData.SetCurrencyAmount(CachedInventoryDisplayData.CurrencyAmount + SellValue);
		InventorySaveData->SetCurrencyAmount(CachedInventoryDisplayData.CurrencyAmount);
		UGameplayStatics::SaveGameToSlot(InventorySaveData, "SaveData", 0);

		OnCurrencyChanged.ExecuteIfBound(CachedInventoryDisplayData.CurrencyAmount);
	}
}


void UINV_InventoryComponent::UpdateDisplayInventoryDataEntry(const FINV_ItemData& ItemData)
{
	TOptional<FINV_ItemDisplayData> ItemDisplayData = CreateItemDisplayData(ItemData);

	if (!ItemDisplayData.IsSet())
	{
		return;
	}
		
	CachedInventoryDisplayData.AddOrUpdateItem(ItemDisplayData.GetValue());
}



FText UINV_InventoryComponent::GetPromptTextByActionType(const FINV_ItemActionType& ActionType) const
{
	if (!ModalPromptTextsData || !ModalPromptTextsData->Prompts.Contains(ActionType))
	{
		return FText::GetEmpty();
	}

	return ModalPromptTextsData->Prompts[ActionType];
}

void UINV_InventoryComponent::ShowItemActionPopup() const
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		UUIS_CommonUIExtensions::PushContentToLayer(PlayerController->GetLocalPlayer(), UI::Layer::Modal, ModalClass);
	}
}

void UINV_InventoryComponent::PerformAction(const FINV_ItemActionType& ActionType, const FINV_ItemIdentification& ItemId, const int32 Amount)
{
	switch (ActionType)
	{
		case FINV_ItemActionType::Drop:
			DropItem(ItemId, Amount);
			break;
		case FINV_ItemActionType::Consume:
			ConsumeItem(ItemId, Amount);
			break;
		case FINV_ItemActionType::Equip:
			TryEquipItem(ItemId);
			break;
		case FINV_ItemActionType::Unequip:
			TryUnequipItem(ItemId);
			break;
		case FINV_ItemActionType::Sell:
			SellItem(ItemId, Amount);
			break;
		default:
			break;
	}
}

TOptional<FINV_ItemDisplayData> UINV_InventoryComponent::CreateItemDisplayData(const FINV_ItemData& ItemDefinition) const
{
	FINV_ItemAssetDefinition* ItemAssetDefinition =  GetItemAssetDefinition(ItemDefinition.ItemIdentification);

	if (ItemAssetDefinition == nullptr)
	{
		return {};
	}

	return FINV_ItemDisplayData(ItemDefinition.ItemIdentification, ItemAssetDefinition, ItemDefinition.Quantity);
}
