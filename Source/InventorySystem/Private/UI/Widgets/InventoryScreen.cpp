// Copyright Paulina Hałatek, All Rights Reserved.

#include "UI/Widgets/InventoryScreen.h"
#include "UI/UIManagerSubsystem.h"
#include "UI/ViewModels/InventoryViewModel.h"
#include "View/MVVMView.h"

void UInventoryScreen::NativeConstruct()
{
	Super::NativeConstruct();
	MVVMView = Cast<UMVVMView>(GetExtension(UMVVMView::StaticClass())); 
}

void UInventoryScreen::NativeOnActivated()
{
	Super::NativeOnActivated();
	
	if (UUIManagerSubsystem* UIManager = GetGameInstance()->GetSubsystem<UUIManagerSubsystem>())
	{
		if (!MVVMView)
		{
			MVVMView->SetViewModelByClass(UIManager->GetInventoryVM());
			UIManager->GetInventoryVM()->SetTestValue(999);
		}
	}
}

void UInventoryScreen::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();
	if (MVVMView)
	{
		MVVMView->SetViewModelByClass(nullptr);
	}
}
