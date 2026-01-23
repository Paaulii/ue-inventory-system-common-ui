// // Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/UIManagerSubsystem.h"

#include "UI/ViewModels/InventoryViewModel.h"

void UUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	InitializeViewModels();
}

void UUIManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
	InventoryViewModel->Deinitialize();
	InventoryViewModel = nullptr;
}

void UUIManagerSubsystem::InitializeViewModels()
{
	InventoryViewModel = NewObject<UInventoryViewModel>(this);

	// TODO: Connect it with Model
	InventoryViewModel->Initialize();
}
