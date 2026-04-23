#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameplayTagContainer.h"
#include "IS_AutoOpenWidgetGameMode.generated.h"

class UCommonActivatableWidget;

UCLASS()
class INVENTORYSYSTEM_API AIS_AutoOpenWidgetGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Widget To Show")
	TSubclassOf<UCommonActivatableWidget> WidgetToOpenClass = {};

	UPROPERTY(EditDefaultsOnly, Category = "Widget To Show", meta = (Categories = "UI.Layer"))
	FGameplayTag LayerStackTag = FGameplayTag::EmptyTag;
};
