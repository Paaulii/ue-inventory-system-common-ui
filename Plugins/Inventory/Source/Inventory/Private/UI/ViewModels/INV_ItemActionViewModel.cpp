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

void UINV_ItemActionViewModel::DelegatePerformAction(const FINV_ItemIdentification& ItemIdentification) const
{
	DelegatePerformAction(SelectedAction, ItemIdentification);
}

void UINV_ItemActionViewModel::DelegatePerformAction(const FINV_ItemActionType& ActionType, const FINV_ItemIdentification& ItemIdentification) const
{
	// TODO: Change to Quantity when implemented
	InventoryComponent->PerformAction(ActionType, ItemIdentification, 1);
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

void UINV_ItemActionViewModel::SetIsSingleItemQuantityAction(bool bState)
{
	UE_MVVM_SET_PROPERTY_VALUE(IsSingleItemQuantityAction, bState);
}