// // Copyright Paulina Hałatek, All Rights Reserved.
#include "Player/CommonPlayerController.h"
#include "Player/CommonLocalPlayer.h"

void ACommonPlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();

	if (UCommonLocalPlayer* LocalPlayer = Cast<UCommonLocalPlayer>(Player))
	{
		LocalPlayer->OnPlayerControllerSet.Broadcast(LocalPlayer, this);
	}
}
