// // Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CommonPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API ACommonPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void ReceivedPlayer() override;	
};
