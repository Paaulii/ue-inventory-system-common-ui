// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/ViewModels/INV_ItemDetailsViewModel.h"

#include "Player/Components/Inventory/INV_InventoryComponent.h"

void UINV_ItemDetailsViewModel::Initialize()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		InventoryComponent = PlayerController->FindComponentByClass<UINV_InventoryComponent>();
	}
}

void UINV_ItemDetailsViewModel::OnDropButtonSelected() const
{
	if (InventoryComponent)
	{
		InventoryComponent->ShowPopup();
	}
}

void UINV_ItemDetailsViewModel::OnConsumeButtonSelected()
{
}

void UINV_ItemDetailsViewModel::OnEquipButtonSelected()
{
}
