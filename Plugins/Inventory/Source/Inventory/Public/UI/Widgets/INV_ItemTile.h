#pragma once

#include "CommonButtonBase.h"
#include "CoreMinimal.h"
#include "INV_ItemTile.generated.h"

class UCommonLazyImage;
class UCommonTextBlock;
class UMVVMView;
class UImage;
class UINV_SelectionViewModel;
class UINV_ItemViewModel;

UCLASS()
class INVENTORY_API UINV_ItemTile : public UCommonButtonBase
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;
	void SetViewModels(UINV_ItemViewModel* ItemVM, UINV_SelectionViewModel* SelectionVM);

private:
	UFUNCTION(BlueprintCallable)
	void VM_OnSelectItemUpdated(const UINV_ItemViewModel* ItemVM);
	
	UFUNCTION(BlueprintCallable)
	void VM_ItemImageUpdated(UTexture2D* Image);

	UFUNCTION(BlueprintCallable)
	void VM_OnIsEquippedUpdated(bool bState);

	UFUNCTION(BlueprintCallable)
	void SetFocusState(bool bState, bool bSkipAnimation);
	
	UFUNCTION(BlueprintCallable)
	void SetHoveredState(bool bState, bool bSkipAnimation);

	UFUNCTION(BlueprintCallable)
	void ResetTile();
	
	UFUNCTION(BlueprintCallable)
	void OnFocused();

	void SetEmptyState(bool bState);
	
	void SetInteractable(bool bState);
	
	void SetEquippedState(bool bState, bool bSkipAnimation);
	
	void SetVisualStateWithAnimation(UWidgetAnimation* Animation, bool bPlayForward, bool bSkipAnimation);
	
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> Hovered = nullptr;
	
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> Selected = nullptr;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> Equipped = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> BackgroundImage = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Item = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float EmptyItemBackgroundFadeValue = 0.0f;
	
	UPROPERTY()
	TObjectPtr<UINV_ItemViewModel> CachedItemVM = nullptr;
	
	UPROPERTY()
	TObjectPtr<UINV_SelectionViewModel> CachedSelectionVM = nullptr;

	UPROPERTY()
	TObjectPtr<UMVVMView> MVVMView = nullptr;
	
	bool bIsSelected = false;
	bool bIsEquipped = false;
	bool bIsEmpty = false;
	bool bIsInteractable = true;
};
