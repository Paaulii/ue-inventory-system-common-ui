#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/INV_Equippable.h"
#include "INV_SkeletalEquippedItem.generated.h"

struct FINV_ItemAssetDefinition;

UCLASS()
class INVENTORY_API AINV_SkeletalEquippedItem : public AActor, public IINV_Equippable
{
	GENERATED_BODY()

public:
	AINV_SkeletalEquippedItem();
	virtual void SetMesh(const FINV_ItemAssetDefinition* ItemDefinition, USkeletalMeshComponent* ParentMeshComponent) const override;

private:
	UPROPERTY()
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent = nullptr;
};
