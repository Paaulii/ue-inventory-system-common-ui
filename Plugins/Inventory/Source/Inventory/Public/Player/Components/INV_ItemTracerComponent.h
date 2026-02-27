// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "INV_ItemTracerComponent.generated.h"


class AINV_PlayerController;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORY_API UINV_ItemTracerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UINV_ItemTracerComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
								   FActorComponentTickFunction* ThisTickFunction) override;

	virtual void BeginPlay() override;
	TObjectPtr<AActor> GetHoveredActor() const { return ThisActor;}
protected:
	void TraceForItem();
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	float TraceLength;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TEnumAsByte<ECollisionChannel> ItemTraceChannel;

private:
	UPROPERTY()
	TObjectPtr<AINV_PlayerController> Owner;

	UPROPERTY()
	TObjectPtr<AActor> ThisActor;

	UPROPERTY()
	TObjectPtr<AActor> LastActor;
};
