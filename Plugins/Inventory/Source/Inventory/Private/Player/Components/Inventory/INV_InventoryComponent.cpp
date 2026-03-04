// Copyright Paulina Hałatek, All Rights Reserved.


#include "Player/Components/Inventory/INV_InventoryComponent.h"

#include "UIS_UIManagerSubsystem.h"
#include "Data/INV_InventoryDataAsset.h"
#include "Data/INV_ModalPromptTexts.h"
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

void UINV_InventoryComponent::TryAddItem(FINV_ItemData& ItemData)
{
	UINV_InventorySaveData* LoadGameInstance = Cast<UINV_InventorySaveData>(UGameplayStatics::LoadGameFromSlot("SaveData", 0));
	if (!LoadGameInstance)
	{
		return;
	}
	
	FINV_ItemAssetDefinition* ItemAssetDefinition = InventoryDataAsset->GetItemDefinition(
			ItemData.ItemIdentification.ItemId,
			ItemData.ItemIdentification.CategoryId
		);
	
	int ReminderQuantityToAdd = ItemData.Quantity;
	const int MaxQuantity = ItemAssetDefinition->MaxQuantity;
	TArray<FINV_ItemData> PlayerSavedItems = CachedPlayerItems.FilterByPredicate([&ItemData, &MaxQuantity](const FINV_ItemData& SaveItemData)
	{
		return  SaveItemData.ItemIdentification.ItemId == ItemData.ItemIdentification.ItemId &&
			SaveItemData.ItemIdentification.CategoryId == ItemData.ItemIdentification.CategoryId &&
				SaveItemData.Quantity < MaxQuantity;
	});

	TArray<int16> UpdatedIndices;
	if (PlayerSavedItems.Num() > 0)
	{
		for (int i = 0 ; i < PlayerSavedItems.Num(); i++)
		{
			int16 QuantityAfterAddition = PlayerSavedItems[i].Quantity + ReminderQuantityToAdd;
			ReminderQuantityToAdd = QuantityAfterAddition - MaxQuantity;

			PlayerSavedItems[i].Quantity = FMath::Clamp(QuantityAfterAddition, 0, MaxQuantity);
			UpdatedIndices.Add(i);
		}
	}

	while (ReminderQuantityToAdd > 0)
	{
		int16 ItemQuantity = ReminderQuantityToAdd;
		
		if (ReminderQuantityToAdd >= MaxQuantity)
		{
			ItemQuantity = MaxQuantity;
			ReminderQuantityToAdd -= MaxQuantity;
		}
		CachedPlayerItems.Add(FINV_ItemData(FINV_ItemIdentification(ItemData.ItemIdentification.ItemId, ItemData.ItemIdentification.CategoryId), ItemQuantity));
		UpdatedIndices.Add(CachedPlayerItems.Num() - 1);
	}
		

	for (auto UpdatedItemIndex : UpdatedIndices)
	{
		FINV_ItemData& SaveItemData = CachedPlayerItems[UpdatedItemIndex];
		TOptional<FINV_ItemDisplayData> ItemDisplayData = CreateItemDisplayData(SaveItemData, UpdatedItemIndex);

		if (!ItemDisplayData.IsSet())
		{
			continue;
		}
		
		CachedInventoryDisplayData.UpdateItem(ItemDisplayData.GetValue());
		LoadGameInstance->UpdateItemDataAtIndex(SaveItemData, UpdatedItemIndex);
	}
	
	UGameplayStatics::SaveGameToSlot(LoadGameInstance, "SaveData", 0);
	OnInventoryDataChanged.ExecuteIfBound(CachedInventoryDisplayData);
}

FText UINV_InventoryComponent::GetPromptTextById(const FName& PromptId) const
{
	if (!ModalPromptTextsData || !ModalPromptTextsData->Prompts.Contains(PromptId))
	{
		return FText::GetEmpty();
	}

	return ModalPromptTextsData->Prompts[PromptId];
}

void UINV_InventoryComponent::ShowPopup()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		UUIS_CommonUIExtensions::PushContentToLayer(PlayerController->GetLocalPlayer(), UI::Layer::Modal, ModalClass);
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
