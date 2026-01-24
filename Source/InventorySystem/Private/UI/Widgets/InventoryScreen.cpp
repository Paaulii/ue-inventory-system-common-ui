// Copyright Paulina Hałatek, All Rights Reserved.

#include "UI/Widgets/InventoryScreen.h"
#include "Data/InventoryData.h"
#include "UI/UIManagerSubsystem.h"
#include "UI/ViewModels/InventoryViewModel.h"
#include "View/MVVMView.h"

UE_DISABLE_OPTIMIZATION

void UInventoryScreen::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	MVVMView = Cast<UMVVMView>(GetExtension(UMVVMView::StaticClass())); 
}

void UInventoryScreen::NativeOnActivated()
{
	Super::NativeOnActivated();
	
	if (UUIManagerSubsystem* UIManager = GetGameInstance()->GetSubsystem<UUIManagerSubsystem>())
	{
		if (MVVMView)
		{
			MVVMView->SetViewModel("InventoryViewModel", UIManager->GetInventoryVM());
			FInventoryData Inventory;
			
			// Set currency
			Inventory.CurrencyAmount = 1000;
			
			FCategoryData ResourcesCategory;
			ResourcesCategory.CategoryName =  FText::FromString("Resources");
			
			FCategoryData WeaponsCategory;
			WeaponsCategory.CategoryName = FText::FromString("Weapons");
			
			FCategoryData ArmorCategory;
			ArmorCategory.CategoryName = FText::FromString("Armor");
			
			// Add category to inventory
			Inventory.Categories.Add(ResourcesCategory);
			Inventory.Categories.Add(WeaponsCategory);
			Inventory.Categories.Add(ArmorCategory);
			UE_LOG(LogTemp, Warning, TEXT("Inventory categories: %d"), Inventory.Categories.Num());
			UIManager->GetInventoryVM()->RebuildInventory(Inventory);
		}
	}
}

void UInventoryScreen::NativeOnDeactivated()
{
	Super::NativeOnDeactivated();
	if (MVVMView)
	{
		MVVMView->SetViewModel("InventoryViewModel",nullptr);
	}
}
