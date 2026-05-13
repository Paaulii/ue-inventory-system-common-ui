#include "UI/MVVM/UIS_MVVMUserWidget.h"

void UUIS_MVVMUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	UIS_ViewModelCacher::Initialize(this);
}

void UUIS_MVVMUserWidget::CacheViewModels(UUIS_MVVMUIManagerSubsystem& UIManager, UMVVMView* View)
{
	this->MVVMView = View;
}

