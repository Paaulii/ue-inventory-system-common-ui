// Copyright Paulina Hałatek, All Rights Reserved.


#include "Player/Components/Inventory/INV_InventoryComponent.h"

#include "UIS_UIManagerSubsystem.h"
#include "Data/INV_InventoryDataAsset.h"
#include "Data/Types/INV_ItemSaveDataTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Player/INV_PlayerController.h"
#include "Player/Data/INV_InventorySaveData.h"
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
	if (UINV_InventorySaveData* LoadGameInstance = Cast<UINV_InventorySaveData>(
		UGameplayStatics::LoadGameFromSlot("SaveData", 0)))
	{
		TArray<FINV_ItemSaveData> CachedInventoryItems = LoadGameInstance->GetInventoryItems();
		TArray<FINV_CategoryDisplayData> CategoryDisplayDataArray = TranslatePlayerItemsToDisplayData(
			CachedInventoryItems);

		const FINV_InventoryDisplayData InventoryDisplayData = FINV_InventoryDisplayData(
			LoadGameInstance->GetCurrencyAmount(),
			LoadGameInstance->GetMaxItemsCapacity(),
			CategoryDisplayDataArray
		);

		OnInventoryDataChanged.ExecuteIfBound(InventoryDisplayData);
	}
}

TArray<FINV_CategoryDisplayData> UINV_InventoryComponent::TranslatePlayerItemsToDisplayData(const TArray<FINV_ItemSaveData>& PlayerItemDataList)
{
	TArray<FINV_CategoryDisplayData> CategoryDisplayDataList;
	
	if (!InventoryDataAsset)
	{
		return CategoryDisplayDataList;
	}
	
	TMap<int, TArray<FINV_ItemDisplayData>*> ItemsPerCategory;

	for (auto& CachedPlayerItem : PlayerItemDataList)
	{
		TInstancedStruct<FINV_ItemAssetDefinition>* ItemAssetDefinition = InventoryDataAsset->Items.FindByPredicate(
			[&CachedPlayerItem](const TInstancedStruct<FINV_ItemAssetDefinition>& Item)
			{
				FINV_ItemAssetDefinition ItemAssetDefinition = Item.Get();

				return ItemAssetDefinition.Id == CachedPlayerItem.IdData.Id && ItemAssetDefinition.CategoryId ==
					CachedPlayerItem.IdData.
					                 CategoryId;
			});

		if (!ItemAssetDefinition)
		{
			continue;
		}

		const FINV_ItemAssetDefinition& ItemAssetRef = ItemAssetDefinition->Get();
		FINV_ItemDisplayData ItemDisplayData = FINV_ItemDisplayData(ItemAssetRef, CachedPlayerItem.Quantity);
		
		if (!ItemsPerCategory.Find(CachedPlayerItem.IdData.CategoryId))
		{
			TArray<FINV_ItemDisplayData> NewList = TArray<FINV_ItemDisplayData>();
			ItemsPerCategory.Add(CachedPlayerItem.IdData.Id, &NewList) ;
		}
		
		TArray<FINV_ItemDisplayData>* ItemList = ItemsPerCategory[CachedPlayerItem.IdData.CategoryId];
		
		
		ItemList->Add(ItemDisplayData);
	}

	

	for (const auto& CurrentCategoryData : InventoryDataAsset->Categories)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *CurrentCategoryData.CategoryName.ToString())

		TArray<FINV_ItemDisplayData> NewList = TArray<FINV_ItemDisplayData>();
		if (ItemsPerCategory.Find(CurrentCategoryData.Id))
		{
			NewList = *ItemsPerCategory[CurrentCategoryData.Id];
		}
		
		CategoryDisplayDataList.Add(FINV_CategoryDisplayData(CurrentCategoryData.CategoryName,NewList));
	}

	return CategoryDisplayDataList;
}


void UINV_InventoryComponent::SaveItemToInventoryData(FINV_ItemSaveData& ItemData)
{
	UINV_InventorySaveData* SaveGameInstance = Cast<UINV_InventorySaveData>(
		UGameplayStatics::CreateSaveGameObject(UINV_InventorySaveData::StaticClass()));
	UWorld* World = GetWorld();

	if (!SaveGameInstance || !World)
	{
		return;
	}

	SaveGameInstance->AddItemToArray(ItemData);
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, "SaveData", 0);
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

	UCommonActivatableWidget* WidgetToActivate = RootLayout->
		PushWidgetToLayerStack(UI::Layer::GameMenu, InventoryClass);

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
