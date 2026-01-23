// Copyright Paulina Hałatek, All Rights Reserved.

#include "UI/Widgets/InventoryScreen.h"
#include "UI/UIManagerSubsystem.h"
#include "UI/ViewModels/InventoryViewModel.h"
#include "View/MVVMView.h"

void UInventoryScreen::NativeOnActivated()
{
	Super::NativeOnActivated();
	
	if (UUIManagerSubsystem* UIManager = GetGameInstance()->GetSubsystem<UUIManagerSubsystem>())
	{
		UMVVMView* MVVMView = Cast<UMVVMView>(GetExtension(UMVVMView::StaticClass()));
		MVVMView->SetViewModelByClass(UIManager->GetInventoryVM());
		UIManager->GetInventoryVM()->SetTestValue(999);
	}
}

void UInventoryScreen::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();
}
