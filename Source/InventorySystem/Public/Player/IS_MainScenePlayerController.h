#pragma once

#include "CoreMinimal.h"
#include "Player/INV_PlayerController.h"
#include "IS_MainScenePlayerController.generated.h"

UCLASS()
class INVENTORYSYSTEM_API AIS_PlayerController : public AINV_PlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
};
