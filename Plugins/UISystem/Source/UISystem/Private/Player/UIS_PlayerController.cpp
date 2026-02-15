// // Copyright Paulina Hałatek, All Rights Reserved.
#include "Player/UIS_PlayerController.h"
#include "Player/UIS_LocalPlayer.h"

void AUIS_PlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();

	if (UUIS_LocalPlayer* LocalPlayer = Cast<UUIS_LocalPlayer>(Player))
	{
		LocalPlayer->OnPlayerControllerSet.Broadcast(LocalPlayer, this);
	}
}

void AUIS_PlayerController::OnPossess(APawn* PossessedPawn)
{
	Super::OnPossess(PossessedPawn);
	OnPawnPossessed.Broadcast();
}
