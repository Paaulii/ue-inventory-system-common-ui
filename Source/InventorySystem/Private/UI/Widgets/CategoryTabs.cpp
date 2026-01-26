// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/CategoryTabs.h"

#include "Components/DynamicEntryBox.h"
#include "UI/UIManagerSubsystem.h"
#include "UI/ViewModels/CategoryViewModel.h"
#include "UI/ViewModels/InventoryViewModel.h"
#include "UI/ViewModels/SelectionViewModel.h"
#include "UI/Widgets/CategoryButtonTab.h"
#include "View/MVVMView.h"

void UCategoryTabs::OnActivated() const
{
	SelectTab(0);
}

void UCategoryTabs::CreateTabs(const TArray<UCategoryViewModel*> CategoryViewModels)
{
	if (CategoryViewModels.Num() <= 0 )
	{
		return;
	}
	
	CacheViewModels();
	ResetTabs();
	for ( UCategoryViewModel* CategoryViewModel : CategoryViewModels)
	{
		UUserWidget* NewTab = TabButtons->CreateEntry();
		if (UCategoryButtonTab* ButtonTab = Cast<UCategoryButtonTab>(NewTab))
		{
			ButtonTab->Setup(CategoryViewModel, SelectionVM);
		}
	}

	if (CategoryViewModels.IsValidIndex(0))
	{
		SelectionVM->SetSelectedCategory(CategoryViewModels[0]);
	}
}

void UCategoryTabs::ChangeCategory(const int Offset) const
{
	UCategoryViewModel* SelectedCategory = SelectionVM->GetSelectedCategory();
	TArray<UCategoryViewModel*> AllCategories = InventoryVM->GetCategories();
	int Index = AllCategories.IndexOfByPredicate([SelectedCategory](const UCategoryViewModel* CategoryViewModel)
	{
		return CategoryViewModel == SelectedCategory;
	});

	Index += Offset;
	SelectTab(Index);
}

void UCategoryTabs::SelectTab(const int Index) const
{
	if (!InventoryVM  || !SelectionVM)
	{
		return;
	}
	
	TArray<UCategoryViewModel*> AllCategories = InventoryVM->GetCategories();
	if (AllCategories.IsValidIndex(Index))
	{
		SelectionVM->SetSelectedCategory(AllCategories[Index]);
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
	if (SelectionVM == nullptr )
	{
		SelectionVM = UIManager->GetSelectionVM();
	}

	if (InventoryVM == nullptr )
	{
		InventoryVM = UIManager->GetInventoryVM();
	}
}
