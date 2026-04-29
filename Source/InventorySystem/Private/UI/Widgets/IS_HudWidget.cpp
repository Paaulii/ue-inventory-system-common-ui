#include "UI/Widgets/IS_HudWidget.h"
#include "UI/MVVM/UIS_MvvmUIManagerSubsystem.h"
#include "UI/ViewModels/INV_PlayerStatViewModel.h"
#include "View/MVVMView.h"

void UIS_HudWidget::CacheViewModels(UUIS_MvvmUIManagerSubsystem& UIManager)
{
	UINV_PlayerStatViewModel* PlayerStatVM = UIManager.GetViewModel<UINV_PlayerStatViewModel>();
	checkf(PlayerStatVM, TEXT("UIManager cannot find PlayerStatViewModel. Check if you added this class to UIManager's ViewModelsToSpawn array."));
	MVVMView->SetViewModel(FName("PlayerStatViewModel"), PlayerStatVM);
	CachedPlayerStatVM = PlayerStatVM;
}