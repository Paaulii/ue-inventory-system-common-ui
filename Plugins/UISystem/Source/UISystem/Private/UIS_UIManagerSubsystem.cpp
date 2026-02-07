#include "UIS_UIManagerSubsystem.h"
#include "UI/UIS_GameUIPolicy.h"

void UUIS_UIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	if (!CurrentPolicy && !DefaultUIPolicyClass.IsNull())
	{
		TSubclassOf<UUIS_GameUIPolicy> PolicyClass = DefaultUIPolicyClass.LoadSynchronous();
		SwitchToPolicy(NewObject<UUIS_GameUIPolicy>(this, PolicyClass));
	}

	//
	// if (CurrentPolicy)
	// {
	// 	return;
	// }
	//
	// const UUIS_UIManagerSubsystem* Defaults =
	// 	GetDefault<UUIS_UIManagerSubsystem>();
	//
	// if (!Defaults->DefaultUIPolicyClass.IsNull())
	// {
	// 	TSubclassOf<UUIS_GameUIPolicy> PolicyClass =
	// 		Defaults->DefaultUIPolicyClass.LoadSynchronous();
	//
	// 	if (PolicyClass)
	// 	{
	// 		SwitchToPolicy(NewObject<UUIS_GameUIPolicy>(this, PolicyClass));
	// 	}
	// }
}

void UUIS_UIManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();

	SwitchToPolicy(nullptr);
}

void UUIS_UIManagerSubsystem::NotifyPlayerAdded(UUIS_LocalPlayer* LocalPlayer)
{
	if (ensure(LocalPlayer) && CurrentPolicy)
	{
		CurrentPolicy->NotifyPlayerAdded(LocalPlayer);
	}
}

void UUIS_UIManagerSubsystem::NotifyPlayerDestroyed(UUIS_LocalPlayer* LocalPlayer)
{
	if (LocalPlayer && CurrentPolicy)
	{
		CurrentPolicy->NotifyPlayerDestroyed(LocalPlayer);
	}
}

void UUIS_UIManagerSubsystem::SwitchToPolicy(UUIS_GameUIPolicy* InPolicy)
{
	if (CurrentPolicy != InPolicy)
	{
		CurrentPolicy = InPolicy;
	}
}