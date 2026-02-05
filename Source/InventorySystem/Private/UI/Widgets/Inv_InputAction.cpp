// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/Inv_InputAction.h"
#include "CommonActionWidget.h"

void UInv_InputAction::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (!CustomInputAction.IsNull())
	{
		UpdateTriggeringInputAction(CustomInputAction);
	}
}

void UInv_InputAction::UpdateTriggeringInputAction(const FDataTableRowHandle& InputAction)
{
	CustomInputAction = InputAction;
	SetTriggeringInputAction(InputAction);
	InputAction_CustomAction->SetInputAction(CustomInputAction);
}

void UInv_InputAction::HandleTriggeringActionCommited()
{
	Super::HandleTriggeringActionCommited();

	if (IsInteractionEnabled())
	{
		OnTriggered.Broadcast();
	}
}
