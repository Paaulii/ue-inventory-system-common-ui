#pragma once

#include "CommonButtonBase.h"
#include "CoreMinimal.h"
#include "INV_CategoryButtonTab.generated.h"

class UINV_SelectionViewModel;
class UINV_CategoryViewModel;

UCLASS()
class INVENTORY_API UINV_CategoryButtonTab : public UCommonButtonBase
{
	GENERATED_BODY()
	
public:
	void Setup(UINV_CategoryViewModel* CategoryVM, UINV_SelectionViewModel* SelectionVM);
	void Deinitialize();
	
private:
	UFUNCTION(BlueprintCallable)
	void UpdateSelectionState(UINV_CategoryViewModel* SelectedCategory);
	
	UFUNCTION(BlueprintCallable)
	void SetSelectedState(bool bIsSelected);
	
	UFUNCTION(BlueprintCallable)
	void SetHoveredState(bool bIsHovered);

	void SetViewModels(UINV_CategoryViewModel* CategoryVM, UINV_SelectionViewModel* SelectionVM);
	void SetAnimationState(UWidgetAnimation* Animation, const bool bIsStateEnabled);
	
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> Hovered = nullptr;
	
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> Selected = nullptr;
	
	UPROPERTY(Transient)
	TObjectPtr<UINV_CategoryViewModel> CachedCategoryVM = nullptr;
	
	UPROPERTY(Transient)
	TObjectPtr<UINV_SelectionViewModel> CachedSelectionVM = nullptr;

	bool bIsSelected = false;
};
