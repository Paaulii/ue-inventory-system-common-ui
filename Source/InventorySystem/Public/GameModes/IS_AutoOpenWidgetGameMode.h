// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/GameMode.h"
#include "IS_AutoOpenWidgetGameMode.generated.h"

class UCommonActivatableWidget;
/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API AIS_AutoOpenWidgetGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Widget To Show")
	TSubclassOf<UCommonActivatableWidget> WidgetToOpenClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget To Show", meta = (Categories = "UI.Layer"))
	FGameplayTag LayerStackTag;
};
