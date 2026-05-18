#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Engine/LocalPlayer.h"
#include "UIS_LocalPlayer.generated.h"

UCLASS()
class UISYSTEM_API UUIS_LocalPlayer : public ULocalPlayer
{
	GENERATED_BODY()
	
public:
	DECLARE_MULTICAST_DELEGATE_TwoParams(FUIS_PlayerControllerSetDelegate, UUIS_LocalPlayer* LocalPlayer, APlayerController* PlayerController);
	FUIS_PlayerControllerSetDelegate OnPlayerControllerSet;

};
