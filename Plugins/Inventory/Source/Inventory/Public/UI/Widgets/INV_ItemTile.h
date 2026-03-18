// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "CommonLoadGuard.h"
#include "INV_ItemTile.generated.h"

class UCommonTextBlock;
class UMVVMView;
class UINV_SelectionViewModel;
class UINV_ItemViewModel;
class UCommonLazyImage;
class UImage;
/**
 * 
 */
UCLASS()
class INVENTORY_API UINV_ItemTile : public UCommonButtonBase
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;
	
	UFUNCTION(BlueprintCallable)
	void VM_OnSelectItemUpdated(UINV_ItemViewModel* ItemVM);
	
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
	
	void SetViewModels(UINV_ItemViewModel* ItemVM, UINV_SelectionViewModel* SelectionVM);
	
	void SetEquippedState(bool bState, bool bSkipAnimation);
	
	void SetVisualStateWithAnimation(UWidgetAnimation* Animation, bool bPlayForward, bool bSkipAnimation);
protected:
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> Hovered;
	
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> Selected;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> Equipped;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Background_Image;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Item;

	UPROPERTY(EditDefaultsOnly)
	float EmptyItemBackgroundFadeValue;
private:
	UPROPERTY()
	TObjectPtr<UINV_ItemViewModel> CachedItemVM;
	
	UPROPERTY()
	TObjectPtr<UINV_SelectionViewModel> CachedSelectionVM;

	UPROPERTY()
	TObjectPtr<UMVVMView> MVVMView;
	
	bool bIsSelected;
	bool bIsEquipped;
	bool bIsEmpty;
	bool bIsInteractable = true;
};
