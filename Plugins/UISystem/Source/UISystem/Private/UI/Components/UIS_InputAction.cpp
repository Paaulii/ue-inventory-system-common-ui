#include "UI/Components//UIS_InputAction.h"
#include "CommonActionWidget.h"

void UUIS_InputAction::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (!CustomInputAction.IsNull())
	{
		UpdateTriggeringInputAction(CustomInputAction);
	}
}

void UUIS_InputAction::UpdateTriggeringInputAction(const FDataTableRowHandle& InputAction)
{
	CustomInputAction = InputAction;
	SetTriggeringInputAction(InputAction);
	InputAction_CustomAction->SetInputAction(CustomInputAction);
}

void UUIS_InputAction::HandleTriggeringActionCommited()
{
	Super::HandleTriggeringActionCommited();

	if (IsInteractionEnabled())
	{
		OnTriggered.Broadcast();
	}
}
