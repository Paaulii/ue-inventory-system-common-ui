// Copyright Paulina Hałatek, All Rights Reserved.


#include "Player/IS_MainScenePlayerController.h"

void AIS_MainScenePlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameOnly());
}
