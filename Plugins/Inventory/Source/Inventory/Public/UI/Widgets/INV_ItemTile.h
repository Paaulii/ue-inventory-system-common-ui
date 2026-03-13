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
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemReady, UINV_ItemTile*, Item);
	FOnItemReady OnItemSelected;
	
	virtual void NativeOnInitialized() override;
	
	UFUNCTION(BlueprintCallable)
	void VM_OnSelectItemUpdated(UINV_ItemViewModel* ItemVM);
	
	UFUNCTION(BlueprintCallable)
	void VM_ItemImageUpdated(UTexture2D* Image);

	UFUNCTION(BlueprintCallable)
	void VM_OnIsEquippedUpdated(bool bState);
	
	// UFUNCTION(BlueprintCallable)
	// void VM_UpdateTileContent(UINV_ItemViewModel* ItemVM);
	//
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

	void SetQuantityVisible(bool bState) const;

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
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> Text_Quantity;
	
	UPROPERTY(EditDefaultsOnly)
	float EmptyItemBackgroundFadeValue;
private:
	UFUNCTION()
	void NotifyOnItemSelected();
	
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

	FWidgetAnimationDynamicEvent AnimationStartedEvent;
};
