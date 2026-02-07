#include "UIS_CommonGameInstance.h"
#include "UIS_UIManagerSubsystem.h"
#include "Player/UIS_LocalPlayer.h"

int32 UUIS_CommonGameInstance::AddLocalPlayer(ULocalPlayer* NewPlayer, FPlatformUserId UserId)
{
	int32 ReturnVal = Super::AddLocalPlayer(NewPlayer, UserId);
	if (ReturnVal != INDEX_NONE)
	{
		if (!PrimaryPlayer.IsValid())
		{
			PrimaryPlayer = NewPlayer;
		}
		
		GetSubsystem<UUIS_UIManagerSubsystem>()->NotifyPlayerAdded(Cast<UUIS_LocalPlayer>(NewPlayer));
	}

	return ReturnVal;
}

bool UUIS_CommonGameInstance::RemoveLocalPlayer(ULocalPlayer* ExistingPlayer)
{
	if (PrimaryPlayer == ExistingPlayer)
	{
		PrimaryPlayer.Reset();
	}
	
	GetSubsystem<UUIS_UIManagerSubsystem>()->NotifyPlayerDestroyed(Cast<UUIS_LocalPlayer>(ExistingPlayer));

	return Super::RemoveLocalPlayer(ExistingPlayer);
}