// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/CategoryTabs.h"

#include "Components/DynamicEntryBox.h"
#include "UI/UIManagerSubsystem.h"
#include "UI/ViewModels/CategoryViewModel.h"
#include "UI/ViewModels/InventoryViewModel.h"
#include "UI/ViewModels/SelectionViewModel.h"
#include "UI/Widgets/CategoryButtonTab.h"
#include "View/MVVMView.h"


void UCategoryTabs::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	//GetViewModels();
}

void UCategoryTabs::CreateTabs(const TArray<UCategoryViewModel*> CategoryViewModels)
{
	if (CategoryViewModels.Num() <= 0 )
	{
		return;
	}
	
	SetViewModelsRef();
	ResetTabs();
	for ( UCategoryViewModel* CategoryViewModel : CategoryViewModels)
	{
		UUserWidget* NewTab = TabButtons->CreateEntry();
		if (UCategoryButtonTab* ButtonTab = Cast<UCategoryButtonTab>(NewTab))
		{
			ButtonTab->Initialize(CategoryViewModel);
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
	if (Index < AllCategories.Num())
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

void UCategoryTabs::SetViewModelsRef()
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
