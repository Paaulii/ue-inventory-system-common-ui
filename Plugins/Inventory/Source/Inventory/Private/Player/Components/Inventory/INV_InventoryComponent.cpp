// Copyright Paulina Hałatek, All Rights Reserved.


#include "Player/Components/Inventory/INV_InventoryComponent.h"

#include "UIS_UIManagerSubsystem.h"
#include "Data/INV_InventoryDataAsset.h"
#include "Data/INV_ModalPromptTexts.h"
#include "Data/Types/INV_ItemActionType.h"
#include "Data/Types/INV_ItemSaveDataTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Player/INV_PlayerController.h"
#include "Player/Data/INV_InventorySaveData.h"
#include "UI/UIS_CommonUIExtensions.h"
#include "UI/UIS_CommonUILayerTags.h"
#include "UI/UIS_GameUIPolicy.h"
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
	// UINV_InventorySaveData* InventorySaveData = Cast<UINV_InventorySaveData>(UGameplayStatics::LoadGameFromSlot("SaveData", 0));
	// if (!InventorySaveData)
	// {
	// 	return;
	// }
	//
	// TArray<FINV_ItemData> Items;
	// InventorySaveData->SetPlayerItems(Items);
	// UGameplayStatics::SaveGameToSlot(InventorySaveData, "SaveData", 0);
	LoadInventoryData();
}

void UINV_InventoryComponent::LoadInventoryData()
{
	if (UINV_InventorySaveData* LoadGameInstance = Cast<UINV_InventorySaveData>(UGameplayStatics::LoadGameFromSlot("SaveData", 0)))
	{
		CachedPlayerItems = LoadGameInstance->GetInventoryItems();
		
		TArray<FINV_CategoryDisplayData> CategoryDisplayDataArray = TranslatePlayerItemsToDisplayData(CachedPlayerItems);

		FINV_InventoryDisplayData InventoryDisplayData = FINV_InventoryDisplayData(
			LoadGameInstance->GetCurrencyAmount(),
			LoadGameInstance->GetMaxItemsCapacity(),
			CategoryDisplayDataArray
		);
		
		CachedInventoryDisplayData = InventoryDisplayData;
		OnInventoryDataChanged.ExecuteIfBound(InventoryDisplayData);
	}
}

void UINV_InventoryComponent::ConsumeItem(const FINV_ItemIdentification& ItemId, const int16 Amount)
{
	DelegateApplyEffects(ItemId);
	FINV_ItemData* CachedItemData = GetCachedItem(ItemId.Id);

	if (!CachedItemData)
	{
		return;
	}
	
	CachedItemData->Quantity = CachedItemData->Quantity - Amount;

	if (CachedItemData->Quantity <= 0)
	{
		CachedPlayerItems.RemoveAll([ItemId](const FINV_ItemData& CurrentItem)
		{
			return CurrentItem.ItemIdentification.Id == ItemId.Id;
		});
		CachedInventoryDisplayData.RemoveItemAt(CachedItemData->ItemIdentification.Id);
	}
	else
	{
		UpdateDisplayInventoryDataEntry(*CachedItemData);
	}
	
	SaveInventoryData(CachedPlayerItems);
	OnInventoryDataChanged.ExecuteIfBound(CachedInventoryDisplayData);
}

void UINV_InventoryComponent::DelegateApplyEffects(const FINV_ItemIdentification& ItemId) const
{
	FINV_ItemAssetDefinition* ItemAssetDef = InventoryDataAsset->GetItemDefinition(ItemId.ItemTag, ItemId.CategoryTag);

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

TArray<FINV_CategoryDisplayData> UINV_InventoryComponent::TranslatePlayerItemsToDisplayData(TArray<FINV_ItemData>& PlayerItemDataList) const
{
	TArray<FINV_CategoryDisplayData> CategoryDisplayDataList;
	
	if (!InventoryDataAsset)
	{
		return CategoryDisplayDataList;
	}
	
	TMap<FGameplayTag, TArray<FINV_ItemDisplayData>*> ItemsPerCategory;
	for (int i = 0; i < PlayerItemDataList.Num(); i++ ) {
		FINV_ItemData& CachedPlayerItem = PlayerItemDataList[i];
		TOptional<FINV_ItemDisplayData> ItemDisplayData = CreateItemDisplayData(CachedPlayerItem);

		if (!ItemDisplayData.IsSet())
		{
			continue;
		}
		
		if (!ItemsPerCategory.Find(CachedPlayerItem.ItemIdentification.CategoryTag))
		{
			TArray<FINV_ItemDisplayData> NewList;
			ItemsPerCategory.Add(CachedPlayerItem.ItemIdentification.CategoryTag, &NewList) ;
		}
		
		TArray<FINV_ItemDisplayData>* ItemList = ItemsPerCategory[CachedPlayerItem.ItemIdentification.CategoryTag];
		
		ItemList->Add(ItemDisplayData.GetValue());
	}

	for (const auto& CurrentCategoryData : InventoryDataAsset->Categories)
	{
		TArray<FINV_ItemDisplayData> NewList;
		if (ItemsPerCategory.Find(CurrentCategoryData.CategoryTag))
		{
			NewList = *ItemsPerCategory[CurrentCategoryData.CategoryTag];
		}

		FINV_CategoryDisplayData NewCategory = FINV_CategoryDisplayData(CurrentCategoryData.CategoryTag, CurrentCategoryData.CategoryName,NewList);
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
	UUIS_UIManagerSubsystem* UIManager = OwningController->GetGameInstance()->GetSubsystem<UUIS_UIManagerSubsystem>();

	if (!UIManager)
	{
		return;
	}

	UUIS_GameUIPolicy* Policy = UIManager->GetCurrentUIPolicy();
	if (!Policy)
	{
		return;
	}

	UUIS_PrimaryGameLayout* RootLayout = Policy->GetRootLayout();
	if (!RootLayout)
	{
		return;
	}

	UCommonActivatableWidget* WidgetToActivate = RootLayout->PushWidgetToLayerStack(UI::Layer::GameMenu, InventoryClass);

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

void UINV_InventoryComponent::TryAddItem(FINV_ItemData& ItemData)
{
	FINV_ItemAssetDefinition* ItemAssetDefinition = InventoryDataAsset->GetItemDefinition(
			ItemData.ItemIdentification.ItemTag,
			ItemData.ItemIdentification.CategoryTag
		);

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
	OnInventoryDataChanged.ExecuteIfBound(CachedInventoryDisplayData);
}

void UINV_InventoryComponent::UpdateDisplayInventoryDataEntry(const FINV_ItemData& ItemData)
{
	
	TOptional<FINV_ItemDisplayData> ItemDisplayData = CreateItemDisplayData(ItemData);

	if (!ItemDisplayData.IsSet())
	{
		return;
	}
		
	CachedInventoryDisplayData.UpdateItem(ItemDisplayData.GetValue());
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
			break;
		case FINV_ItemActionType::Consume:
			ConsumeItem(ItemId, Amount);
			break;
		case FINV_ItemActionType::Equip:
			break;
		default:
			break;
	}
}

TOptional<FINV_ItemDisplayData> UINV_InventoryComponent::CreateItemDisplayData(const FINV_ItemData& ItemDefinition) const
{
	FINV_ItemAssetDefinition* ItemAssetDefinition = InventoryDataAsset->GetItemDefinition(
			ItemDefinition.ItemIdentification.ItemTag,
			ItemDefinition.ItemIdentification.CategoryTag
		);

	if (ItemAssetDefinition == nullptr)
	{
		return {};
	}

	return FINV_ItemDisplayData(ItemDefinition.ItemIdentification, ItemAssetDefinition, ItemDefinition.Quantity);
}
