#include "UI/Widgets/IS_HudWidget.h"
#include "UI/MVVM/UIS_MVVMUIManagerSubsystem.h"
#include "UI/ViewModels/INV_InteractionViewModel.h"
#include "UI/ViewModels/INV_PlayerStatViewModel.h"
#include "View/MVVMView.h"

void UIS_HudWidget::CacheViewModels(UUIS_MVVMUIManagerSubsystem& UIManager, UMVVMView* View)
{
	Super::CacheViewModels(UIManager, View);
	
	UINV_PlayerStatViewModel* PlayerStatVM = UIManager.GetViewModel<UINV_PlayerStatViewModel>();
	checkf(PlayerStatVM, TEXT("UIManager cannot find PlayerStatViewModel. Check if you added this class to UIManager's ViewModelsToSpawn array."));
	MVVMView->SetViewModel(FName("PlayerStatViewModel"), PlayerStatVM);

	UINV_InteractionViewModel* InteractionVM = UIManager.GetViewModel<UINV_InteractionViewModel>();
	checkf(PlayerStatVM, TEXT("UIManager cannot find InteractionViewModel. Check if you added this class to UIManager's ViewModelsToSpawn array."));
	MVVMView->SetViewModel(FName("InteractionViewModel"), InteractionVM);
}