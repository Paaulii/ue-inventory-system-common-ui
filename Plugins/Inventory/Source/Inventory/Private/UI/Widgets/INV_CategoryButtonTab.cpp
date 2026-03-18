// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/INV_CategoryButtonTab.h"
#include "Animation/WidgetAnimation.h"
#include "UI/ViewModels/INV_CategoryViewModel.h"
#include "UI/ViewModels/INV_SelectionViewModel.h"
#include "View/MVVMView.h"

void UINV_CategoryButtonTab::Setup(UINV_CategoryViewModel* CategoryVM, UINV_SelectionViewModel* SelectionVM)
{
	SetViewModels(CategoryVM, SelectionVM);
}

void UINV_CategoryButtonTab::Deinitialize()
{
	SetViewModels(nullptr, nullptr);
	bIsSelected = false;
}

void UINV_CategoryButtonTab::SetViewModels(UINV_CategoryViewModel* CategoryVM, UINV_SelectionViewModel* SelectionVM)
{
	if (UMVVMView* MVVMView = Cast<UMVVMView>(GetExtension(UMVVMView::StaticClass())))
	{
		MVVMView->SetViewModel("CategoryViewModel", CategoryVM);
		MVVMView->SetViewModel("SelectionViewModel", SelectionVM);
		CachedCategoryVM = CategoryVM;
		CachedSelectionVM = SelectionVM;
	}
}

void UINV_CategoryButtonTab::UpdateSelectionState(UINV_CategoryViewModel* SelectedCategory)
{
	bool bIsNowSelected = SelectedCategory == CachedCategoryVM;
	SetSelectedState(bIsNowSelected);
}

void UINV_CategoryButtonTab::SetSelectedState(bool bIsNowSelected)
{
	bool bStateHasChanged = bIsSelected != bIsNowSelected;

	if (!bStateHasChanged)
	{
		return;
	}

	bIsSelected = bIsNowSelected;
	StopAnimation(Selected);
	SetAnimationState(Selected, bIsSelected);
}

void UINV_CategoryButtonTab::SetHoveredState(bool bIsHovered)
{
	SetAnimationState(Hovered, bIsHovered);
}

void UINV_CategoryButtonTab::SetAnimationState(UWidgetAnimation* Animation, const bool bIsStateEnabled)
{
	if (!Animation)
	{
		return;
	}

	if (bIsStateEnabled)
	{
		PlayAnimationForward(Animation);
	}
	else
	{
		PlayAnimationReverse(Animation);
	}
}
