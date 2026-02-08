// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "INV_CategoryButtonTab.generated.h"

class UINV_SelectionViewModel;
class UINV_CategoryViewModel;
/**
 * 
 */
UCLASS()
class INVENTORY_API UINV_CategoryButtonTab : public UCommonButtonBase
{
	GENERATED_BODY()
public:
	void Setup(UINV_CategoryViewModel* CategoryVM, UINV_SelectionViewModel* SelectionVM);
	void Deinitialize();
protected:
	void SetViewModels(UINV_CategoryViewModel* CategoryVM, UINV_SelectionViewModel* SelectionVM);
	
	UFUNCTION(BlueprintCallable)
	void UpdateSelectionState(UINV_CategoryViewModel* SelectedCategory);
	
	UFUNCTION(BlueprintCallable)
	void SetSelectedState(bool bIsSelected);
	
	UFUNCTION(BlueprintCallable)
	void SetHoveredState(bool bIsHovered);

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> Hovered;
	
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> Selected;
private:
	UPROPERTY(Transient)
	TObjectPtr<UINV_CategoryViewModel> CachedCategoryVM;
	
	UPROPERTY(Transient)
	TObjectPtr<UINV_SelectionViewModel> CachedSelectionVM;

	void SetAnimationState(UWidgetAnimation* Animation, const bool bIsStateEnabled);
	bool bIsSelected = false;
};
