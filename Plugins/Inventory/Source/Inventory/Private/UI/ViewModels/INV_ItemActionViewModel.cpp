// Copyright Paulina Hałatek, All Rights Reserved.

#include "UI/ViewModels/INV_ItemActionViewModel.h"
#include "Player/Components/Inventory/INV_InventoryComponent.h"

void UINV_ItemActionViewModel::Initialize()
{
	Super::Initialize();
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		InventoryComponent = PlayerController->FindComponentByClass<UINV_InventoryComponent>();
	}
}

void UINV_ItemActionViewModel::SetSelectedAction(const FINV_ItemActionType& Action)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(SelectedAction, Action))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetPromptText);
	}
}

void UINV_ItemActionViewModel::SetIsSingleItemQuantityAction(bool bState)
{
	UE_MVVM_SET_PROPERTY_VALUE(IsSingleItemQuantityAction, bState);
}

void UINV_ItemActionViewModel::DelegateShowItemActionPopup() const
{
	InventoryComponent->ShowItemActionPopup();
}

FText UINV_ItemActionViewModel::GetPromptText() const
{
	if (!InventoryComponent)
	{
		return FText::GetEmpty();
	}

	return InventoryComponent->GetPromptTextByActionType(SelectedAction);
}

void UINV_ItemActionViewModel::DelegatePerformAction(const FINV_ItemActionType& ActionType, const FINV_ItemIdentification& ItemIdentification) const
{
	InventoryComponent->PerformAction(ActionType, ItemIdentification);
}

void UINV_ItemActionViewModel::DelegatePerformAction(const FINV_ItemIdentification& ItemIdentification) const
{
	DelegatePerformAction(SelectedAction, ItemIdentification);
}
