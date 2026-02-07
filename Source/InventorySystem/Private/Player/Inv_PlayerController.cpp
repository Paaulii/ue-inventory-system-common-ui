// // Copyright Paulina Hałatek, All Rights Reserved.
#include "Player/Inv_PlayerController.h"
#include "Player/UIS_LocalPlayer.h"

void AInv_PlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();

	if (UUIS_LocalPlayer* LocalPlayer = Cast<UUIS_LocalPlayer>(Player))
	{
		LocalPlayer->OnPlayerControllerSet.Broadcast(LocalPlayer, this);
	}
}
