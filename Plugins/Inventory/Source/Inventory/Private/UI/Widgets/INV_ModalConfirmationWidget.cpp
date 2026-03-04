// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/INV_ModalConfirmationWidget.h"
#include "Components/Image.h"
#include "UI/MVVM/UIS_MvvmUIManagerSubsystem.h"
#include "View/MVVMView.h"
#include "UI/ViewModels/INV_SelectionViewModel.h"
#include "UI/ViewModels/INV_PromptViewModel.h"

void UINV_ModalConfirmationWidget::VM_SelectedItemChanged(UINV_ItemViewModel* ItemVM)
{
	Image_Icon->SetBrushFromTexture(ItemVM->GetSmallImage());
	// TODO: Prompt description
}

void UINV_ModalConfirmationWidget::CacheViewModels(UUIS_MvvmUIManagerSubsystem* UIManager)
{
	UINV_SelectionViewModel* SelectionVM = UIManager->GetViewModel<UINV_SelectionViewModel>();
	MVVMView->SetViewModel("SelectionViewModel", SelectionVM);
	CachedSelectionVM = SelectionVM;

	UINV_PromptViewModel* PromptVM = UIManager->GetViewModel<UINV_PromptViewModel>();
	MVVMView->SetViewModel("PromptViewModel", PromptVM);
	CachedPromptVM = PromptVM;
}

void UINV_ModalConfirmationWidget::ClearViewModelsCache()
{
	MVVMView->SetViewModel("SelectionViewModel", nullptr);
	MVVMView->SetViewModel("PromptViewModel", nullptr);
	CachedSelectionVM = nullptr;
	CachedPromptVM = nullptr;
}