// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/INV_ActivatableMvvmWidget.h"
#include "UI/INV_UIManagerSubsystem.h"
#include "View/MVVMView.h"

void UINV_ActivatableMvvmWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	MVVMView = Cast<UMVVMView>(GetExtension(UMVVMView::StaticClass()));
}

void UINV_ActivatableMvvmWidget::NativeOnActivated()
{
	Super::NativeOnActivated();
	if (UINV_UIManagerSubsystem* UIManager = GetGameInstance()->GetSubsystem<UINV_UIManagerSubsystem>())
	{
		if (MVVMView)
		{
			CacheViewModels(UIManager);
		}
	}
}

void UINV_ActivatableMvvmWidget::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	if (MVVMView)
	{
		ClearViewModelsCache();
	}
}
