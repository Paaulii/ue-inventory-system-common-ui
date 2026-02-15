// // Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/MVVM/UIS_MvvmUIManagerSubsystem.h"

#include "UI/MVVM/UIS_ViewModelBase.h"

void UUIS_MvvmUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	InitializeViewModels();
}

void UUIS_MvvmUIManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
	DeinitializeViewModels();
}

bool UUIS_MvvmUIManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return this->GetClass()->IsInBlueprint() && Super::ShouldCreateSubsystem(Outer);
}

void UUIS_MvvmUIManagerSubsystem::InitializeViewModels()
{
	for (auto ViewModelClass : ViewModelsToSpawn)
	{
		auto NewViewModel = NewObject<UUIS_ViewModelBase>(this, ViewModelClass);
		ViewModels.Add(NewViewModel);
		NewViewModel->Initialize();
	}
}

void UUIS_MvvmUIManagerSubsystem::DeinitializeViewModels()
{
	for (auto ViewModel : ViewModels)
	{
		ViewModel->Deinitialize();
	}

	ViewModels.Empty();
}
