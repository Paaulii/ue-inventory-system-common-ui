#include "UI/Widgets/INV_InputAction.h"
#include "CommonActionWidget.h"

void UINV_InputAction::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (!CustomInputAction.IsNull())
	{
		UpdateTriggeringInputAction(CustomInputAction);
	}
}

void UINV_InputAction::UpdateTriggeringInputAction(const FDataTableRowHandle& InputAction)
{
	CustomInputAction = InputAction;
	SetTriggeringInputAction(InputAction);
	InputAction_CustomAction->SetInputAction(CustomInputAction);
}

void UINV_InputAction::HandleTriggeringActionCommited()
{
	Super::HandleTriggeringActionCommited();

	if (IsInteractionEnabled())
	{
		OnTriggered.Broadcast();
	}
}
