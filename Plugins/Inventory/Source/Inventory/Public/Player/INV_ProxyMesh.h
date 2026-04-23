#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "INV_ProxyMesh.generated.h"

class UINV_EquipmentComponent;
class USpringArmComponent;

UCLASS()
class INVENTORY_API AINV_ProxyMesh : public AActor
{
	GENERATED_BODY()

public:
	AINV_ProxyMesh();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	UFUNCTION()
	void SetupMesh(APawn* OldPawn, APawn* NewPawn);

	UFUNCTION()
	void OnItemAttached(AActor* AttachedItem);

	UFUNCTION()
	void OnItemDetached(AActor* DetachedItem);
	
	void WaitForPawnPossession();
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UINV_EquipmentComponent> EquipmentComponent = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArmComponent = nullptr;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneCaptureComponent2D> SceneCaptureComponent = nullptr;
		
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USkeletalMeshComponent> Mesh = nullptr;
	
	TWeakObjectPtr<USkeletalMeshComponent> SourceMesh = nullptr;
};
