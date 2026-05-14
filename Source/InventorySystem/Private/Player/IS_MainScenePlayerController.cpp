#include "Player/IS_MainScenePlayerController.h"

void AIS_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameOnly());
}
