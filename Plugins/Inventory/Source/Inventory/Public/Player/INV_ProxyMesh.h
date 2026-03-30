// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "INV_ProxyMesh.generated.h"

class USpringArmComponent;
class UINV_EquipmentComponent;

UCLASS()
class INVENTORY_API AINV_ProxyMesh : public AActor
{
	GENERATED_BODY()

public:
	AINV_ProxyMesh();
protected:
	virtual void BeginPlay() override;
private:
	UFUNCTION()
	void SetupMesh(APawn* OldPawn, APawn* NewPawn);

	UFUNCTION()
	void OnItemAttached(AActor* AttachedItem);

	UFUNCTION()
	void OnItemDetached(AActor* DetachedItem);
	
	void WaitForPawnPossession();
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UINV_EquipmentComponent> EquipmentComponent;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneCaptureComponent2D> SceneCaptureComponent;
		
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> Mesh;
	
	TWeakObjectPtr<USkeletalMeshComponent> SourceMesh;
};
