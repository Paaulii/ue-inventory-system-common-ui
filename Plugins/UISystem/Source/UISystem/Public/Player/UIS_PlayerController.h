// // Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UIS_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UISYSTEM_API AUIS_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void ReceivedPlayer() override;	
};
