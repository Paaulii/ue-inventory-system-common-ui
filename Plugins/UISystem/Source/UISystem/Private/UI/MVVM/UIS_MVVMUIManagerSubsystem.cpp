#include "UI/MVVM/UIS_MVVMUIManagerSubsystem.h"
#include "Player/UIS_LocalPlayer.h"
#include "Player/UIS_PlayerController.h"
#include "UI/MVVM/UIS_ViewModelBase.h"

void UUIS_MVVMUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	InitializeViewModels();
}

void UUIS_MVVMUIManagerSubsystem::Deinitialize()
{
	DeinitializeViewModels();
	Super::Deinitialize();
}

void UUIS_MVVMUIManagerSubsystem::InitializeViewModels()
{
	for (const auto& ViewModelClass : ViewModelsToSpawn)
	{
		auto NewViewModel = NewObject<UUIS_ViewModelBase>(this, ViewModelClass);
		ViewModels.Add(NewViewModel);
	}
}

void UUIS_MVVMUIManagerSubsystem::DeinitializeViewModels()
{
	for (const auto& ViewModel : ViewModels)
	{
		if (ViewModel.Get())
		{
			ViewModel->Deinitialize();
		}
	}

	ViewModels.Empty();
}

bool UUIS_MVVMUIManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return GetClass()->IsInBlueprint() && Super::ShouldCreateSubsystem(Outer);
}

void UUIS_MVVMUIManagerSubsystem::NotifyPlayerAdded(UUIS_LocalPlayer* LocalPlayer)
{
	Super::NotifyPlayerAdded(LocalPlayer);

	LocalPlayer->OnPlayerControllerSet.AddWeakLambda(
		this, [this](UUIS_LocalPlayer* LocalPlayer, APlayerController* PlayerController)
		{
			if (AUIS_PlayerController* Controller = Cast<AUIS_PlayerController>(PlayerController))
			{
				Controller->OnPossessedPawnChanged.AddDynamic(this, &UUIS_MVVMUIManagerSubsystem::OnPawnPossessed);
			}
		});
}

void UUIS_MVVMUIManagerSubsystem::OnPawnPossessed(APawn* OldPawn, APawn* NewPawn)
{
	if (NewPawn)
	{
		for (const auto& ViewModel : ViewModels)
		{
			ViewModel->Initialize();
		};	
	}
}