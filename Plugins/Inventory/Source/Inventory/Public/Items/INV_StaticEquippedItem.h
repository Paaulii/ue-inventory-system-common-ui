#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/INV_Equippable.h"
#include "INV_StaticEquippedItem.generated.h"

UCLASS()
class INVENTORY_API AINV_StaticEquippedItem : public AActor, public IINV_Equippable
{
	GENERATED_BODY()

public:
	AINV_StaticEquippedItem();
	virtual void SetMesh(const FINV_ItemAssetDefinition* ItemDefinition) const override;
	
private:
	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent = nullptr;
};
