// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/ItemTile.h"

#include "Animation/WidgetAnimation.h"
#include "UI/ViewModels/ItemViewModel.h"
#include "UI/ViewModels/SelectionViewModel.h"
#include "View/MVVMView.h"
#include "CommonLazyImage.h"
#include "Components/Image.h"

void UItemTile::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	MVVMView = Cast<UMVVMView>(GetExtension(UMVVMView::StaticClass()));
	FWidgetAnimationDynamicEvent AnimationEvent;
	AnimationEvent.BindDynamic(this, &UItemTile::NotifyOnItemSelected);
	BindToAnimationFinished(Selected, AnimationEvent);
}

void UItemTile::SetViewModels(UItemViewModel* ItemVM, USelectionViewModel* SelectionVM)
{
	ResetTile();
	
	if (MVVMView)
	{
		MVVMView->SetViewModel("ItemViewModel", ItemVM);
		MVVMView->SetViewModel("SelectionViewModel", SelectionVM);

		CachedItemVM = ItemVM;
		CachedSelectionVM = SelectionVM;
	}

	SetEmptyState(ItemVM == nullptr);
}

void UItemTile::VM_OnSelectItemUpdated(UItemViewModel* ItemVM)
{
	if (ItemVM == nullptr)
	{
		return;
	}
	
	bool bShouldFocus = ItemVM == CachedItemVM;

	if (bIsSelected != bShouldFocus)
	{
		SetFocusState(bShouldFocus, false);
	}
}

void UItemTile::VM_ItemImageUpdated(UTexture2D* Image)
{
	Item->SetBrushFromTexture(Image);
}

void UItemTile::VM_OnIsEquippedUpdated(bool bState)
{
	if (bIsEquipped == bState)
	{
		return;
	}
	
	SetEquippedState(bState, false );
}

void UItemTile::SetFocusState(bool bState, bool bSkipAnimation)
{
	bIsSelected = bState;
	SetVisualStateWithAnimation(Selected, bIsSelected, bSkipAnimation);
}

void UItemTile::SetEquippedState(bool bState, bool bSkipAnimation)
{
	bIsEquipped = bState;
	SetVisualStateWithAnimation(Equipped, bIsEquipped, bSkipAnimation );
}

void UItemTile::SetHoveredState(bool bState, bool bSkipAnimation)
{
	if (bIsSelected || bIsEmpty)
	{
		return;
	}
	
	SetVisualStateWithAnimation(Hovered, bState, bSkipAnimation );
}

void UItemTile::ResetTile()
{
	SetFocusState(false, true);
	SetEquippedState(false, true);
	SetHoveredState(false, true);
}

void UItemTile::OnFocused()
{
	if (CachedSelectionVM == nullptr )
	{
		return;
	}

	CachedSelectionVM->SetSelectedItem(CachedItemVM);
}

void UItemTile::SetEmptyState(bool bState)
{
	bIsEmpty = bState;
	SetIsFocusable(!bIsEmpty);
	SetIsSelectable(!bIsEmpty);
	Background_Image->SetRenderOpacity(bState ? EmptyItemBackgroundFadeValue: 1.f);
	Item->SetRenderOpacity(bState ? 0.f: 1.f);
}

void UItemTile::SetVisualStateWithAnimation(UWidgetAnimation* Animation, bool bPlayForward, bool bSkipAnimation)
{
	float AnimationStartTime = bSkipAnimation? Animation->GetEndTime() : 0;
	EUMGSequencePlayMode::Type PlayModeType =  bPlayForward ? EUMGSequencePlayMode::Forward: EUMGSequencePlayMode::Reverse;
	float AnimationPlaySpeed = !bSkipAnimation && !bPlayForward? 1.5 : 1.0;
	
	PlayAnimation(Animation,AnimationStartTime,1,PlayModeType,AnimationPlaySpeed);
}

void UItemTile::NotifyOnItemSelected()
{
	OnItemSelected.Broadcast(this);
}
