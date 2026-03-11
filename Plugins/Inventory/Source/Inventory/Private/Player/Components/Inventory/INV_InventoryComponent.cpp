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
	LoadInventoryData();
}

void UINV_InventoryComponent::LoadInventoryData()
{
	if (UINV_InventorySaveData* LoadGameInstance = Cast<UINV_InventorySaveData>(UGameplayStatics::LoadGameFromSlot("SaveData", 0)))
	{
		TArray<FINV_ItemData>& CachedInventoryItems = LoadGameInstance->GetInventoryItems();
		CachedPlayerItems = CachedInventoryItems;
		
		TArray<FINV_CategoryDisplayData> CategoryDisplayDataArray = TranslatePlayerItemsToDisplayData(CachedInventoryItems);

		FINV_InventoryDisplayData InventoryDisplayData = FINV_InventoryDisplayData(
			LoadGameInstance->GetCurrencyAmount(),
			LoadGameInstance->GetMaxItemsCapacity(),
			CategoryDisplayDataArray
		);
		
		CachedInventoryDisplayData = InventoryDisplayData;
		OnInventoryDataChanged.ExecuteIfBound(InventoryDisplayData);
	}
}

void UINV_InventoryComponent::ConsumeItem(const FINV_ItemIdentification& ItemId)
{
	UE_LOG(LogTemp, Warning, TEXT("Consume Item"));
}

TArray<FINV_CategoryDisplayData> UINV_InventoryComponent::TranslatePlayerItemsToDisplayData(TArray<FINV_ItemData>& PlayerItemDataList) const
{
	TArray<FINV_CategoryDisplayData> CategoryDisplayDataList;
	
	if (!InventoryDataAsset)
	{
		return CategoryDisplayDataList;
	}
	
	TMap<FName, TArray<FINV_ItemDisplayData>*> ItemsPerCategory;

	for (int i = 0; i < PlayerItemDataList.Num(); i++ ) {
		FINV_ItemData& CachedPlayerItem = PlayerItemDataList[i];
		TOptional<FINV_ItemDisplayData> ItemDisplayData = CreateItemDisplayData(CachedPlayerItem, i);

		if (!ItemDisplayData.IsSet())
		{
			continue;
		}
		
		if (!ItemsPerCategory.Find(CachedPlayerItem.ItemIdentification.CategoryId))
		{
			TArray<FINV_ItemDisplayData> NewList;
			ItemsPerCategory.Add(CachedPlayerItem.ItemIdentification.CategoryId, &NewList) ;
		}
		
		TArray<FINV_ItemDisplayData>* ItemList = ItemsPerCategory[CachedPlayerItem.ItemIdentification.CategoryId];
		
		ItemList->Add(ItemDisplayData.GetValue());
	}

	for (const auto& CurrentCategoryData : InventoryDataAsset->Categories)
	{
		TArray<FINV_ItemDisplayData> NewList;
		if (ItemsPerCategory.Find(CurrentCategoryData.Id))
		{
			NewList = *ItemsPerCategory[CurrentCategoryData.Id];
		}

		FINV_CategoryDisplayData NewCategory = FINV_CategoryDisplayData(CurrentCategoryData.Id, CurrentCategoryData.CategoryName,NewList);
		CategoryDisplayDataList.Add(NewCategory);
	}

	return CategoryDisplayDataList;
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
			ItemData.ItemIdentification.ItemId,
			ItemData.ItemIdentification.CategoryId
		);
	
	int ReminderQuantityToAdd = ItemData.Quantity;
	const int MaxQuantity = ItemAssetDefinition->MaxQuantity;

	if (CachedPlayerItems.Num() > 0)
	{
		for (int i = 0 ; i < CachedPlayerItems.Num(); i++)
		{
			FINV_ItemData& CurrentItemData = CachedPlayerItems[i];
			if (CurrentItemData.ItemIdentification.ItemId != ItemData.ItemIdentification.ItemId ||
			CurrentItemData.ItemIdentification.CategoryId != ItemData.ItemIdentification.CategoryId ||
				CurrentItemData.Quantity >= MaxQuantity)
			{
				continue;
			}
				
			int16 QuantityAfterAddition = CurrentItemData.Quantity + ReminderQuantityToAdd;
			ReminderQuantityToAdd = QuantityAfterAddition - MaxQuantity;

			CurrentItemData.Quantity = FMath::Clamp(QuantityAfterAddition, 0, MaxQuantity);
			UpdateDisplayInventoryDataEntry(i);
		}
	}

	while (ReminderQuantityToAdd > 0)
	{
		int16 ItemQuantity = ReminderQuantityToAdd;
		
		if (ReminderQuantityToAdd >= MaxQuantity)
		{
			ItemQuantity = MaxQuantity;
		}
		
		CachedPlayerItems.Add(FINV_ItemData(FINV_ItemIdentification(ItemData.ItemIdentification.ItemId, ItemData.ItemIdentification.CategoryId), ItemQuantity));
		UpdateDisplayInventoryDataEntry(CachedPlayerItems.Num() - 1);
		ReminderQuantityToAdd -= ItemQuantity;
	}

	SaveInventoryData(CachedPlayerItems);
	OnInventoryDataChanged.ExecuteIfBound(CachedInventoryDisplayData);
}

void UINV_InventoryComponent::UpdateDisplayInventoryDataEntry(int16 EntryIndexToUpdate)
{
	TOptional<FINV_ItemDisplayData> ItemDisplayData = CreateItemDisplayData(CachedPlayerItems[EntryIndexToUpdate], EntryIndexToUpdate);

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

void UINV_InventoryComponent::ShowPopup() const
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		UUIS_CommonUIExtensions::PushContentToLayer(PlayerController->GetLocalPlayer(), UI::Layer::Modal, ModalClass);
	}
}

void UINV_InventoryComponent::PerformAction(const FINV_ItemActionType& ActionType,   const FINV_ItemIdentification& ItemId)
{
	switch (ActionType)
	{
		case FINV_ItemActionType::Drop:
			break;
		case FINV_ItemActionType::Consume:
			ConsumeItem(ItemId);
			break;
		case FINV_ItemActionType::Equip:
			break;
		default:
			break;
	}
}

TOptional<FINV_ItemDisplayData> UINV_InventoryComponent::CreateItemDisplayData(const FINV_ItemData& ItemDefinition, int16 SaveDataIndex) const
{
	FINV_ItemAssetDefinition* ItemAssetDefinition = InventoryDataAsset->GetItemDefinition(
			ItemDefinition.ItemIdentification.ItemId,
			ItemDefinition.ItemIdentification.CategoryId
		);

	if (ItemAssetDefinition == nullptr)
	{
		return {};
	}

	return FINV_ItemDisplayData(SaveDataIndex, ItemAssetDefinition, ItemDefinition.Quantity);
}
