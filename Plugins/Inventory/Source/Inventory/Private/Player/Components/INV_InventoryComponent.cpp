// Copyright Paulina Hałatek, All Rights Reserved.


#include "Player/Components/INV_InventoryComponent.h"

#include "UIS_UIManagerSubsystem.h"
#include "Kismet/GameplayStatics.h"
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
	OwningController = Cast<APlayerController>(GetOwner());
	LoadInventoryData();
}

void UINV_InventoryComponent::LoadInventoryData()
{
	if (UINV_InventorySaveData* LoadGameInstance = Cast<UINV_InventorySaveData>(UGameplayStatics::LoadGameFromSlot("SaveData", 0)))
	{
		CachedInventoryItems = LoadGameInstance->GetInventoryItems();
		// TODO: Update VM
	}
}

void UINV_InventoryComponent::SaveItemToInventoryData(FINV_ItemData& ItemData)
{
	UINV_InventorySaveData* SaveGameInstance = Cast<UINV_InventorySaveData>(UGameplayStatics::CreateSaveGameObject(UINV_InventorySaveData::StaticClass()));
	UWorld* World = GetWorld();

	if (!SaveGameInstance || !World)
	{
		return;
	}

	SaveGameInstance->AddItemToArray(ItemData);
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, "SaveData", 0)
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
