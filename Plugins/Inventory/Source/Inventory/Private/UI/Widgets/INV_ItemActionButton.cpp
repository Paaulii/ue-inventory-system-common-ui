// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/INV_ItemActionButton.h"

void UINV_ItemActionButton::SetHoveredState(bool bState)
{
	SetVisualStateWithAnimation(Hovered, bState);
	
}

void UINV_ItemActionButton::SetEnabledState(bool bState)
{
	SetVisualStateWithAnimation(Disabled, bState);
}

void UINV_ItemActionButton::SetButtonVisibility(bool bState)
{
	SetVisibility(bState ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

void UINV_ItemActionButton::SetVisualStateWithAnimation(UWidgetAnimation* Animation, bool bPlayForward)
{
	EUMGSequencePlayMode::Type PlayModeType =  bPlayForward ? EUMGSequencePlayMode::Forward: EUMGSequencePlayMode::Reverse;
	PlayAnimation(Animation,0,1,PlayModeType);
}
