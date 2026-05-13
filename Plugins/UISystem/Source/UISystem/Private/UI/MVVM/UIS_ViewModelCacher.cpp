#include "UI/MVVM/UIS_ViewModelCacher.h"
#include "Blueprint/UserWidget.h"
#include "UI/MVVM/UIS_MVVMUIManagerSubsystem.h"
#include "View/MVVMView.h"

void UIS_ViewModelCacher::Initialize(const UUserWidget* UserWidgetContext)
{
	UMVVMView* MVVMView = Cast<UMVVMView>(UserWidgetContext->GetExtension(UMVVMView::StaticClass()));
	
	if (UUIS_MVVMUIManagerSubsystem* UIManager = UserWidgetContext->GetGameInstance()->GetSubsystem<UUIS_MVVMUIManagerSubsystem>())
	{
		if (MVVMView)
		{
			CacheViewModels(*UIManager, MVVMView);
		}
	}
}
