// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UIS_LocalPlayer.generated.h"

/**
 * 
 */
UCLASS()
class UISYSTEM_API UUIS_LocalPlayer : public ULocalPlayer
{
	GENERATED_BODY()
public:
	/** Called when the local player is assigned a player controller */
	DECLARE_MULTICAST_DELEGATE_TwoParams(FPlayerControllerSetDelegate, UUIS_LocalPlayer* LocalPlayer, APlayerController* PlayerController);
	FPlayerControllerSetDelegate OnPlayerControllerSet;

};
