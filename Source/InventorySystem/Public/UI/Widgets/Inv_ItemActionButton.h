// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "Inv_ItemActionButton.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UInv_ItemActionButton : public UCommonButtonBase
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	void SetHoveredState(bool bState);
	
	UFUNCTION(BlueprintCallable)
	void SetEnabledState(bool bState);
private:
	void SetVisualStateWithAnimation(UWidgetAnimation* Animation, bool bPlayForward);
	
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation>  Hovered;
	
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> Disabled;
};
