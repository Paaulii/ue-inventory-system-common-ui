#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "INV_ItemTracerComponent.generated.h"

class AINV_PlayerController;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORY_API UINV_ItemTracerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UINV_ItemTracerComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	TObjectPtr<AActor> GetHoveredActor() const { return ThisActor; }
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	float TraceLength = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TEnumAsByte<ECollisionChannel> ItemTraceChannel;

private:
	void TraceForItem();
	
	UPROPERTY()
	TObjectPtr<AINV_PlayerController> Owner = nullptr;

	UPROPERTY()
	TObjectPtr<AActor> ThisActor = nullptr;

	UPROPERTY()
	TObjectPtr<AActor> LastActor = nullptr;
};
