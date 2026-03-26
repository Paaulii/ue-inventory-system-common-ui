// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/INV_CharacterDetails.h"
#include "UI/ViewModels/INV_PlayerStatViewModel.h"
#include "UI/MVVM/UIS_MvvmUIManagerSubsystem.h"
#include "View/MVVMView.h"

void UINV_CharacterDetails::CacheViewModels(UUIS_MvvmUIManagerSubsystem* UIManager)
{
	UINV_PlayerStatViewModel* PlayerStatVM = UIManager->GetViewModel<UINV_PlayerStatViewModel>();
	MVVMView->SetViewModel("PlayerStatViewModel", PlayerStatVM);
	CachedPlayerStatVM = PlayerStatVM;
}

void UINV_CharacterDetails::ClearViewModelsCache()
{
	CachedPlayerStatVM = nullptr;
	MVVMView->SetViewModel("PlayerStatViewModel", nullptr);
}
