// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/INV_ItemDetails.h"

#include "Components/Image.h"
#include "UI/ViewModels/INV_SelectionViewModel.h"
#include "UI/MVVM/UIS_MvvmUIManagerSubsystem.h"
#include "View/MVVMView.h"


void UINV_ItemDetails::VM_SelectedItemImageUpdated(UTexture2D* Image)
{
	Image_SelectedItem->SetBrushFromTexture(Image);
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

