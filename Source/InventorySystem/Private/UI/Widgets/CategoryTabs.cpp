// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/CategoryTabs.h"

#include "Components/DynamicEntryBox.h"
#include "UI/UIManagerSubsystem.h"
#include "UI/ViewModels/CategoryViewModel.h"
#include "UI/ViewModels/InventoryViewModel.h"
#include "UI/ViewModels/SelectionViewModel.h"
#include "UI/Widgets/CategoryButtonTab.h"
#include "View/MVVMView.h"

void UCategoryTabs::VM_CreateTabs(const TArray<UCategoryViewModel*> CategoryViewModels)
{
	if (CategoryViewModels.Num() <= 0 )
	{
		return;
	}
	
	ResetTabs();
	CacheViewModels();
	for ( UCategoryViewModel* CategoryViewModel : CategoryViewModels)
	{
		UUserWidget* NewTab = TabButtons->CreateEntry();
		if (UCategoryButtonTab* ButtonTab = Cast<UCategoryButtonTab>(NewTab))
		{
			ButtonTab->Setup(CategoryViewModel, CacheSelectionVM);
		}
	}

	if (CategoryViewModels.IsValidIndex(0))
	{
		CacheSelectionVM->SetSelectedCategory(CategoryViewModels[0]);
	}
}

void UCategoryTabs::ChangeCategory(const int Offset) const
{
	UCategoryViewModel* SelectedCategory = CacheSelectionVM->GetSelectedCategory();
	TArray<UCategoryViewModel*> AllCategories = CacheInventoryVM->GetCategories();
	int Index = AllCategories.IndexOfByPredicate([SelectedCategory](const UCategoryViewModel* CategoryViewModel)
	{
		return CategoryViewModel == SelectedCategory;
	});

	Index += Offset;
	SelectTab(Index);
}

void UCategoryTabs::SelectTab(const int Index) const
{
	if (!CacheInventoryVM  || !CacheSelectionVM)
	{
		return;
	}
	
	TArray<UCategoryViewModel*> AllCategories = CacheInventoryVM->GetCategories();
	if (AllCategories.IsValidIndex(Index))
	{
		CacheSelectionVM->SetSelectedCategory(AllCategories[Index]);
	}
}

void UCategoryTabs::ResetTabs() const
{
	for (UUserWidget* Tab : TabButtons->GetAllEntries())
	{
		if (UCategoryButtonTab* ButtonTab = Cast<UCategoryButtonTab>(Tab))
		{
			ButtonTab->Deinitialize();
		}
	}
	
	TabButtons->Reset();
}

void UCategoryTabs::CacheViewModels()
{
	UUIManagerSubsystem* UIManager = GetGameInstance()->GetSubsystem<UUIManagerSubsystem>();
	if (CacheSelectionVM == nullptr )
	{
		CacheSelectionVM = UIManager->GetSelectionVM();
	}

	if (CacheInventoryVM == nullptr )
	{
		CacheInventoryVM = UIManager->GetInventoryVM();
	}
}
