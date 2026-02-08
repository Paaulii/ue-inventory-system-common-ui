// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/INV_CategoryTabs.h"

#include "Components/DynamicEntryBox.h"
#include "UI/INV_UIManagerSubsystem.h"
#include "UI/ViewModels/INV_CategoryViewModel.h"
#include "UI/ViewModels/INV_InventoryViewModel.h"
#include "UI/ViewModels/INV_SelectionViewModel.h"
#include "UI/Widgets/INV_CategoryButtonTab.h"
#include "View/MVVMView.h"

void UINV_CategoryTabs::VM_CreateTabs(const TArray<UINV_CategoryViewModel*> CategoryViewModels)
{
	if (CategoryViewModels.Num() <= 0 )
	{
		return;
	}
	
	ResetTabs();
	CacheViewModels();
	for ( UINV_CategoryViewModel* CategoryViewModel : CategoryViewModels)
	{
		UUserWidget* NewTab = TabButtons->CreateEntry();
		if (UINV_CategoryButtonTab* ButtonTab = Cast<UINV_CategoryButtonTab>(NewTab))
		{
			ButtonTab->Setup(CategoryViewModel, CacheSelectionVM);
		}
	}

	if (CategoryViewModels.IsValidIndex(0))
	{
		CacheSelectionVM->SetSelectedCategory(CategoryViewModels[0]);
	}
}

void UINV_CategoryTabs::ChangeCategory(const int Offset) const
{
	UINV_CategoryViewModel* SelectedCategory = CacheSelectionVM->GetSelectedCategory();
	TArray<UINV_CategoryViewModel*> AllCategories = CacheInventoryVM->GetCategories();
	int Index = AllCategories.IndexOfByPredicate([SelectedCategory](const UINV_CategoryViewModel* CategoryViewModel)
	{
		return CategoryViewModel == SelectedCategory;
	});

	Index += Offset;
	SelectTab(Index);
}

void UINV_CategoryTabs::SelectTab(const int Index) const
{
	if (!CacheInventoryVM  || !CacheSelectionVM)
	{
		return;
	}
	
	TArray<UINV_CategoryViewModel*> AllCategories = CacheInventoryVM->GetCategories();
	if (AllCategories.IsValidIndex(Index))
	{
		CacheSelectionVM->SetSelectedCategory(AllCategories[Index]);
	}
}

void UINV_CategoryTabs::ResetTabs() const
{
	for (UUserWidget* Tab : TabButtons->GetAllEntries())
	{
		if (UINV_CategoryButtonTab* ButtonTab = Cast<UINV_CategoryButtonTab>(Tab))
		{
			ButtonTab->Deinitialize();
		}
	}
	
	TabButtons->Reset();
}

void UINV_CategoryTabs::CacheViewModels()
{
	UINV_UIManagerSubsystem* UIManager = GetGameInstance()->GetSubsystem<UINV_UIManagerSubsystem>();
	if (CacheSelectionVM == nullptr )
	{
		CacheSelectionVM = UIManager->GetSelectionVM();
	}

	if (CacheInventoryVM == nullptr )
	{
		CacheInventoryVM = UIManager->GetInventoryVM();
	}
}
