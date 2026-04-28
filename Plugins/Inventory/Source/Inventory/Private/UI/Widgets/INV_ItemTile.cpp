#include "UI/Widgets/INV_ItemTile.h"
#include "Animation/WidgetAnimation.h"
#include "CommonLazyImage.h"
#include "Components/Image.h"
#include "UI/ViewModels/INV_SelectionViewModel.h"
#include "View/MVVMView.h"

void UINV_ItemTile::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	MVVMView = Cast<UMVVMView>(GetExtension(UMVVMView::StaticClass()));
}

void UINV_ItemTile::SetViewModels(UINV_ItemViewModel* ItemVM, UINV_SelectionViewModel* SelectionVM)
{
	ResetTile();
	
	if (MVVMView)
	{
		CachedItemVM = ItemVM;
		CachedSelectionVM = SelectionVM;
		MVVMView->SetViewModel(FName("ItemViewModel"),ItemVM);
		MVVMView->SetViewModel(FName("SelectionViewModel"), SelectionVM);
	}

	SetEmptyState(ItemVM == nullptr);
}

void UINV_ItemTile::VM_OnSelectItemUpdated(const UINV_ItemViewModel* ItemVM)
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

void UINV_ItemTile::VM_ItemImageUpdated(UTexture2D* Image)
{
	Item->SetBrushFromTexture(Image);
}

void UINV_ItemTile::VM_OnIsEquippedUpdated(bool bState)
{
	if (bIsEquipped == bState)
	{
		return;
	}
	
	SetEquippedState(bState, false);
}

void UINV_ItemTile::SetFocusState(bool bState, bool bSkipAnimation)
{
	if (!bIsInteractable)
	{
		return;
	}
	
	bIsSelected = bState;
	SetVisualStateWithAnimation(Selected, bIsSelected, bSkipAnimation);
}

void UINV_ItemTile::SetEquippedState(bool bState, bool bSkipAnimation)
{
	bIsEquipped = bState;
	SetVisualStateWithAnimation(Equipped, bIsEquipped, bSkipAnimation );
}

void UINV_ItemTile::SetHoveredState(bool bState, bool bSkipAnimation)
{
	if (bIsSelected || bIsEmpty || !bIsInteractable)
	{
		return;
	}
	
	SetVisualStateWithAnimation(Hovered, bState, bSkipAnimation );
}

void UINV_ItemTile::ResetTile()
{
	SetFocusState(false, true);
	SetEquippedState(false, true);
	SetHoveredState(false, true);
}

void UINV_ItemTile::OnFocused()
{
	if (CachedSelectionVM == nullptr )
	{
		return;
	}

	CachedSelectionVM->SetSelectedItem(CachedItemVM);
}

void UINV_ItemTile::SetEmptyState(bool bState)
{
	bIsEmpty = bState;
	SetIsFocusable(!bIsEmpty);
	SetIsSelectable(!bIsEmpty);
	BackgroundImage->SetRenderOpacity(bState ? EmptyItemBackgroundFadeValue: 1.0f);
	Item->SetRenderOpacity(bState ? 0.0f: 1.0f);
}

void UINV_ItemTile::SetInteractable(bool bState)
{
	bIsInteractable = bState;
}

void UINV_ItemTile::SetVisualStateWithAnimation(UWidgetAnimation* Animation, bool bPlayForward, bool bSkipAnimation)
{
	float AnimationStartTime = bSkipAnimation ? Animation->GetEndTime() : 0.0f;
	EUMGSequencePlayMode::Type PlayModeType =  bPlayForward ? EUMGSequencePlayMode::Forward: EUMGSequencePlayMode::Reverse;
	float AnimationPlaySpeed = (!bSkipAnimation && !bPlayForward) ? 1.5f : 1.0f;

	PlayAnimation(Animation, AnimationStartTime, 1, PlayModeType, AnimationPlaySpeed);
}