#include "Player/IS_MainScenePlayerController.h"

void AIS_MainScenePlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameOnly());
}
