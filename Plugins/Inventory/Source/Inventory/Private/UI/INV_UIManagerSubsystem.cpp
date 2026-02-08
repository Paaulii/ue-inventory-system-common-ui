// // Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/INV_UIManagerSubsystem.h"

#include "UI/ViewModels/INV_InventoryViewModel.h"
#include "UI/ViewModels/INV_SelectionViewModel.h"

void UINV_UIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	InitializeViewModels();
}

void UINV_UIManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
	InventoryViewModel->Deinitialize();
	InventoryViewModel = nullptr;
}

void UINV_UIManagerSubsystem::InitializeViewModels()
{
	InventoryViewModel = NewObject<UINV_InventoryViewModel>(this);

	// TODO: Connect it with Model
	InventoryViewModel->Initialize();

	SelectionViewModel = NewObject<UINV_SelectionViewModel>(this);
}
