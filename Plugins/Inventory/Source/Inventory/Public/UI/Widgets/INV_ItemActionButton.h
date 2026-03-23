// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "INV_ItemActionButton.generated.h"

class UINV_InputAction;
class UCommonTextBlock;
/**
 * 
 */
UCLASS()
class INVENTORY_API UINV_ItemActionButton : public UCommonButtonBase
{
	GENERATED_BODY()
public:
	virtual void NativePreConstruct() override;
	void SetButtonVisibility(bool bState);
protected:
	UFUNCTION(BlueprintCallable)
	void SetHoveredState(bool bState);
	
	UFUNCTION(BlueprintCallable)
	void SetEnabledState(bool bState);

	void SetButtonText(const FText& NewText) const;
	
	UPROPERTY(EditInstanceOnly, Category="Label")
	FText ButtonText;
	
	UPROPERTY(EditInstanceOnly, Category = "Custom Input")
	FDataTableRowHandle ClickInputAction;
private:
	void SetVisualStateWithAnimation(UWidgetAnimation* Animation, bool bPlayForward);
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UINV_InputAction> Button_InputAction;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> Text_Label;
	
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation>  Hovered;
	
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> Disabled;
};
