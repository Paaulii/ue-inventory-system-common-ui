// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/Inv_ItemActionButton.h"

void UInv_ItemActionButton::SetHoveredState(bool bState)
{
	SetVisualStateWithAnimation(Hovered, bState);
	
}

void UInv_ItemActionButton::SetEnabledState(bool bState)
{
	SetVisualStateWithAnimation(Disabled, bState);
}

void UInv_ItemActionButton::SetVisualStateWithAnimation(UWidgetAnimation* Animation, bool bPlayForward)
{
	EUMGSequencePlayMode::Type PlayModeType =  bPlayForward ? EUMGSequencePlayMode::Forward: EUMGSequencePlayMode::Reverse;
	PlayAnimation(Animation,0,1,PlayModeType);
}
