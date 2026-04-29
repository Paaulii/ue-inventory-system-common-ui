#pragma once

#include "CoreMinimal.h"
#include "INV_ActivatableMvvmWidget.h"
#include "Components/Slider.h"
#include "INV_ModalConfirmationWidget.generated.h"

class UCommonTextBlock;
class UHorizontalBox;
class UImage;
class UINV_ItemActionViewModel;
class UINV_ItemViewModel;
class UINV_SelectionViewModel;

UCLASS()
class INVENTORY_API UINV_ModalConfirmationWidget : public UINV_ActivatableMvvmWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;
protected:
	virtual void CacheViewModels(UUIS_MvvmUIManagerSubsystem& UIManager) override;
	
	UFUNCTION(BlueprintCallable)
	void VM_ToggleQuantityDisplayInfo(bool bState);
	
	UFUNCTION(BlueprintCallable)
	void VM_SetupSlider(const int32 ItemQuantity);
	
	UFUNCTION(BlueprintCallable)
	void VM_OnItemImageChanged(UTexture2D* ItemImage);
	
private:
	UFUNCTION(BlueprintCallable)
	void OnConfirmAction();
	
	UFUNCTION()
	void OnSliderValueChanged(float Value);
	
	UFUNCTION()
	void SnapSliderToValue();
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> SliderParent = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USlider> QuantitySlider = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> LeftSliderValueText = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> RightSliderValueText = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> QuantityText = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ImageIcon = nullptr;
	
	UPROPERTY()
	TObjectPtr<UINV_ItemActionViewModel> CachedItemActionVM = nullptr;

	UPROPERTY()
	TObjectPtr<UINV_SelectionViewModel> CachedSelectionVM = nullptr;

	int32 MaxValue = 0;
};
