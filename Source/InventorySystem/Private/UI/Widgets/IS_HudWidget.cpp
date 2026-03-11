// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/IS_HudWidget.h"

#include "UI/MVVM/UIS_MvvmUIManagerSubsystem.h"
#include "UI/ViewModels/INV_PlayerStatViewModel.h"
#include "View/MVVMView.h"

void UIS_HudWidget::CacheViewModels(UUIS_MvvmUIManagerSubsystem* UIManager)
{
	UINV_PlayerStatViewModel* PlayerStatVM = UIManager->GetViewModel<UINV_PlayerStatViewModel>();
	MVVMView->SetViewModel("PlayerStatViewModel", PlayerStatVM);
	CachedPlayerStatVM = PlayerStatVM;
}

void UIS_HudWidget::ClearViewModelsCache()
{
	MVVMView->SetViewModel("PlayerStatViewModel", nullptr);
	CachedPlayerStatVM = nullptr;
}
