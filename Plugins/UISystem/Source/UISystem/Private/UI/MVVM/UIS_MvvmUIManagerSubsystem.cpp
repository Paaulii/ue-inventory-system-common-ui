// // Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/MVVM/UIS_MvvmUIManagerSubsystem.h"

#include "Player/UIS_LocalPlayer.h"
#include "Player/UIS_PlayerController.h"
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

void UUIS_MvvmUIManagerSubsystem::NotifyPlayerAdded(UUIS_LocalPlayer* LocalPlayer)
{
	Super::NotifyPlayerAdded(LocalPlayer);

	LocalPlayer->OnPlayerControllerSet.AddWeakLambda(
		this, [this](UUIS_LocalPlayer* LocalPlayer, APlayerController* PlayerController)
		{
			if (AUIS_PlayerController* Controller = Cast<AUIS_PlayerController>(PlayerController))
			{
				Controller->OnPawnPossessed.AddUObject(this, &UUIS_MvvmUIManagerSubsystem::OnPawnPossessed);
			}
		});
}

void UUIS_MvvmUIManagerSubsystem::OnPawnPossessed()
{
	for (auto ViewModel : ViewModels)
	{
		ViewModel->Initialize();
	};
}

void UUIS_MvvmUIManagerSubsystem::InitializeViewModels()
{
	for (auto ViewModelClass : ViewModelsToSpawn)
	{
		auto NewViewModel = NewObject<UUIS_ViewModelBase>(this, ViewModelClass);
		ViewModels.Add(NewViewModel);
	}
}

void UUIS_MvvmUIManagerSubsystem::DeinitializeViewModels()
{
	for (auto ViewModel : ViewModels)
	{
		if (ViewModel.Get())
		{
			ViewModel->Deinitialize();
		}
	}

	ViewModels.Empty();
}
