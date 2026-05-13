#include "UI/MVVM/UIS_MVVMActivatableWidget.h"

void UUIS_MVVMActivatableWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	UIS_ViewModelCacher::Initialize(this);
}

void UUIS_MVVMActivatableWidget::CacheViewModels(UUIS_MVVMUIManagerSubsystem& UIManager, UMVVMView* View)
{
	this->MVVMView = View;
}
