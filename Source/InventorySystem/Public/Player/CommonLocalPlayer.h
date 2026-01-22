// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CommonLocalPlayer.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UCommonLocalPlayer : public ULocalPlayer
{
	GENERATED_BODY()
public:
	/** Called when the local player is assigned a player controller */
	DECLARE_MULTICAST_DELEGATE_TwoParams(FPlayerControllerSetDelegate, UCommonLocalPlayer* LocalPlayer, APlayerController* PlayerController);
	FPlayerControllerSetDelegate OnPlayerControllerSet;

};
