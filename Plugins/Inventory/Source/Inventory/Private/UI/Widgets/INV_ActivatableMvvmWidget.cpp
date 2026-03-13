// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/INV_ActivatableMvvmWidget.h"
#include "UI/MVVM/UIS_MvvmUIManagerSubsystem.h"
#include "View/MVVMView.h"

void UINV_ActivatableMvvmWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	MVVMView = Cast<UMVVMView>(GetExtension(UMVVMView::StaticClass()));
}

void UINV_ActivatableMvvmWidget::NativeOnActivated()
{
	Super::NativeOnActivated();
	if (UUIS_MvvmUIManagerSubsystem* UIManager = GetGameInstance()->GetSubsystem<UUIS_MvvmUIManagerSubsystem>())
	{
		if (MVVMView)
		{
			CacheViewModels(UIManager);
		}
	}
}

void UINV_ActivatableMvvmWidget::NativeOnDeactivated()
{
	if (MVVMView)
	{
		ClearViewModelsCache();
	}
	
	Super::NativeOnDeactivated();
}
