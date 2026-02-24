// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/INV_ItemDetails.h"

#include "Components/Image.h"
#include "UI/ViewModels/INV_SelectionViewModel.h"
#include "UI/MVVM/UIS_MvvmUIManagerSubsystem.h"
#include "View/MVVMView.h"
#include "CommonTextBlock.h"

void UINV_ItemDetails::VM_SelectedItemUpdated(UINV_ItemViewModel* SelectedItem)
{
	bool bIsItemEmpty = SelectedItem == nullptr;
	SetVisibility(bIsItemEmpty? ESlateVisibility::Hidden : ESlateVisibility::Visible);
	
	if (bIsItemEmpty)
	{
			return;
	}
	
	Text_Name->SetText(SelectedItem->GetItemName());
	Text_Description->SetText(SelectedItem->GetDescription());
	Text_Value->SetText(FText::AsNumber(SelectedItem->GetCurrencyValue()));
	Image_SelectedItem->SetBrushFromTexture(SelectedItem->GetLargeImage());
}


void UINV_ItemDetails::CacheViewModels(UUIS_MvvmUIManagerSubsystem* UIManager)
{
	UINV_SelectionViewModel* SelectionVM = UIManager->GetViewModel<UINV_SelectionViewModel>();
	MVVMView->SetViewModel("SelectionViewModel", SelectionVM);
	CachedSelectionVM = SelectionVM;
}

void UINV_ItemDetails::ClearViewModelsCache()
{
	MVVMView->SetViewModel("SelectionViewModel", nullptr);
	CachedSelectionVM = nullptr;
}

