// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/INV_ItemDetails.h"

#include "Components/Image.h"
#include "UI/ViewModels/INV_SelectionViewModel.h"
#include "UI/INV_UIManagerSubsystem.h"
#include "View/MVVMView.h"


void UINV_ItemDetails::VM_SelectedItemImageUpdated(UTexture2D* Image)
{
	Image_SelectedItem->SetBrushFromTexture(Image);
}

void UINV_ItemDetails::CacheViewModels(UINV_UIManagerSubsystem* UIManager)
{
	MVVMView->SetViewModel("SelectionViewModel", UIManager->GetSelectionVM());
	CachedSelectionVM = UIManager->GetSelectionVM();
}

void UINV_ItemDetails::ClearViewModelsCache()
{
	MVVMView->SetViewModel("SelectionViewModel", nullptr);
	CachedSelectionVM = nullptr;
}

