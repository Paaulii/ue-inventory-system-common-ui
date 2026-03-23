// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/INV_ItemActionButton.h"
#include "CommonTextBlock.h"
#include "UI/Widgets/INV_InputAction.h"

void UINV_ItemActionButton::SetHoveredState(bool bState)
{
	SetVisualStateWithAnimation(Hovered, bState);
	
}

void UINV_ItemActionButton::SetEnabledState(bool bState)
{
	SetVisualStateWithAnimation(Disabled, bState);
}

void UINV_ItemActionButton::NativePreConstruct()
{
	Super::NativePreConstruct();
	SetButtonText(ButtonText);

	if (Button_InputAction)
	{
		Button_InputAction->UpdateTriggeringInputAction(ClickInputAction);
	}
}

void UINV_ItemActionButton::SetButtonVisibility(bool bState)
{
	SetVisibility(bState ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

void UINV_ItemActionButton::SetButtonText(const FText& NewText) const
{
	Text_Label->SetText(NewText);
}

void UINV_ItemActionButton::SetVisualStateWithAnimation(UWidgetAnimation* Animation, bool bPlayForward)
{
	EUMGSequencePlayMode::Type PlayModeType =  bPlayForward ? EUMGSequencePlayMode::Forward: EUMGSequencePlayMode::Reverse;
	PlayAnimation(Animation,0,1,PlayModeType);
}
