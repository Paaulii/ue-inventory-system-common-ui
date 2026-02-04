// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/Inv_ItemDetails.h"

#include "Components/Image.h"
#include "UI/ViewModels/SelectionViewModel.h"
#include "UI/UIManagerSubsystem.h"
#include "View/MVVMView.h"


void UInv_ItemDetails::VM_SelectedItemImageUpdated(UTexture2D* Image)
{
	Image_SelectedItem->SetBrushFromTexture(Image);
}

void UInv_ItemDetails::CacheViewModels(UUIManagerSubsystem* UIManager)
{
	MVVMView->SetViewModel("SelectionViewModel", UIManager->GetSelectionVM());
	CachedSelectionVM = UIManager->GetSelectionVM();
}

void UInv_ItemDetails::ClearViewModelsCache()
{
	MVVMView->SetViewModel("SelectionViewModel", nullptr);
	CachedSelectionVM = nullptr;
}

