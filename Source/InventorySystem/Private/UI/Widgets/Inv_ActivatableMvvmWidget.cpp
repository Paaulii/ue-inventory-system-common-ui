// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/Inv_ActivatableMvvmWidget.h"
#include "UI/UIManagerSubsystem.h"
#include "View/MVVMView.h"

void UInv_ActivatableMvvmWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	MVVMView = Cast<UMVVMView>(GetExtension(UMVVMView::StaticClass()));
}

void UInv_ActivatableMvvmWidget::NativeOnActivated()
{
	Super::NativeOnActivated();
	if (UUIManagerSubsystem* UIManager = GetGameInstance()->GetSubsystem<UUIManagerSubsystem>())
	{
		if (MVVMView)
		{
			CacheViewModels(UIManager);
		}
	}
}

void UInv_ActivatableMvvmWidget::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();

	if (MVVMView)
	{
		ClearViewModelsCache();
	}
}
