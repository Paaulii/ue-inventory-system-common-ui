#include "UI/ViewModels/INV_ItemActionViewModel.h"
#include "Player/Components/Inventory/INV_InventoryComponent.h"

void UINV_ItemActionViewModel::Initialize()
{
	Super::Initialize();
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		InventoryComponent = PlayerController->FindComponentByClass<UINV_InventoryComponent>();
		checkf(InventoryComponent,TEXT("PlayerController doesn't contain InventoryComponent! Make sure to add that component otherwise Inventory System won't work."));
	}
}

void UINV_ItemActionViewModel::DelegatePerformAction(const UINV_ItemViewModel& ItemViewModel, int32 Quantity) const
{
	DelegatePerformAction(SelectedAction, ItemViewModel.GetItemIdentification(), Quantity);
}

void UINV_ItemActionViewModel::DelegatePerformAction(const FINV_ItemActionType& ActionType, const UINV_ItemViewModel& ItemViewModel) const
{
	DelegatePerformAction(ActionType, ItemViewModel.GetItemIdentification(), ItemViewModel.GetQuantity());
}

void UINV_ItemActionViewModel::DelegatePerformAction(const FINV_ItemActionType& ActionType, const FINV_ItemIdentification& ItemIdentification, int32 Quantity) const
{
	InventoryComponent->PerformAction(ActionType, ItemIdentification, Quantity);
}

void UINV_ItemActionViewModel::DelegateShowItemActionPopup() const
{
	InventoryComponent->ShowItemActionPopup();
}

const FText& UINV_ItemActionViewModel::VM_GetPromptText() const
{
	if (!InventoryComponent)
	{
		return FText::GetEmpty();
	}

	return InventoryComponent->GetPromptTextByActionType(SelectedAction);
}

void UINV_ItemActionViewModel::SetSelectedAction(const FINV_ItemActionType& Action)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(SelectedAction, Action))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(VM_GetPromptText);
	}
}
