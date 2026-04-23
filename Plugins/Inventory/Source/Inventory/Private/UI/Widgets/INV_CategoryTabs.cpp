#include "UI/Widgets/INV_CategoryTabs.h"
#include "Components/DynamicEntryBox.h"
#include "UI/MVVM/UIS_MvvmUIManagerSubsystem.h"
#include "UI/Widgets/INV_CategoryButtonTab.h"
#include "UI/ViewModels/INV_CategoryViewModel.h"
#include "UI/ViewModels/INV_InventoryViewModel.h"
#include "UI/ViewModels/INV_SelectionViewModel.h"

void UINV_CategoryTabs::VM_CreateTabs(const TArray<UINV_CategoryViewModel*> CategoryViewModels)
{
	if (CategoryViewModels.Num() <= 0)
	{
		return;
	}
	
	ResetTabs();
	CacheViewModels();
	for (UINV_CategoryViewModel* CategoryViewModel : CategoryViewModels)
	{
		UUserWidget* NewTab = TabButtons->CreateEntry();
		if (UINV_CategoryButtonTab* ButtonTab = Cast<UINV_CategoryButtonTab>(NewTab))
		{
			ButtonTab->Setup(CategoryViewModel, CacheSelectionVM);
		}
	}
}

void UINV_CategoryTabs::CacheViewModels()
{
	UUIS_MvvmUIManagerSubsystem* UIManager = GetGameInstance()->GetSubsystem<UUIS_MvvmUIManagerSubsystem>();

	if (CacheSelectionVM == nullptr)
	{
		CacheSelectionVM = UIManager->GetViewModel<UINV_SelectionViewModel>();
	}

	if (CacheInventoryVM == nullptr)
	{
		CacheInventoryVM = UIManager->GetViewModel<UINV_InventoryViewModel>();
	}
}

void UINV_CategoryTabs::ChangeCategory(const int32 Offset) const
{
	const UINV_CategoryViewModel* SelectedCategory = CacheSelectionVM->GetSelectedCategory();
	TArray<UINV_CategoryViewModel*> AllCategories = CacheInventoryVM->GetCategories();
	int Index = AllCategories.IndexOfByPredicate([SelectedCategory](const UINV_CategoryViewModel* CategoryViewModel)
	{
		return CategoryViewModel == SelectedCategory;
	});

	Index += Offset;
	SelectTab(Index);
}

void UINV_CategoryTabs::SelectTab(const int32 Index) const
{
	if (!CacheInventoryVM || !CacheSelectionVM)
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