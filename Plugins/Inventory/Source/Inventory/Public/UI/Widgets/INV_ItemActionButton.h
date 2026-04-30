#pragma once

#include "CommonButtonBase.h"
#include "CoreMinimal.h"
#include "INV_ItemActionButton.generated.h"

class UCommonTextBlock;
class UINV_InputAction;

UCLASS()
class INVENTORY_API UINV_ItemActionButton : public UCommonButtonBase
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct() override;
	void SetButtonVisibility(bool bState);

private:
	UFUNCTION(BlueprintCallable)
	void SetHoveredState(bool bState);
	
	void SetButtonText(const FText& NewText) const;
	void SetVisualStateWithAnimation(UWidgetAnimation* Animation, bool bPlayForward);
	
	UPROPERTY(EditInstanceOnly)
	FText ButtonText = {};
	
	UPROPERTY(EditInstanceOnly, Category = "Input Action Button | Custom Click Action")
	FDataTableRowHandle ClickInputAction = {};

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UINV_InputAction> InputActionButton = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> TextLabel = nullptr;
	
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> Hovered = nullptr;
};
