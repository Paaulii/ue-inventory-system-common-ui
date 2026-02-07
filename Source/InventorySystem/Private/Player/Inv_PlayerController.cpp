// // Copyright Paulina Hałatek, All Rights Reserved.
#include "Player/Inv_PlayerController.h"
#include "Player/CommonLocalPlayer.h"

void AInv_PlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();

	if (UCommonLocalPlayer* LocalPlayer = Cast<UCommonLocalPlayer>(Player))
	{
		LocalPlayer->OnPlayerControllerSet.Broadcast(LocalPlayer, this);
	}
}
