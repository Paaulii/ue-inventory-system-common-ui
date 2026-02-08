// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/UIS_PlayerController.h"
#include "INV_PlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class INVENTORY_API AINV_PlayerController : public AUIS_PlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TObjectPtr<UInputMappingContext> DefaultIMC;

	UPROPERTY(EditDefaultsOnly, Category ="Inventory")
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TObjectPtr<UInputAction> OpenInventoryAction;

protected:
	UFUNCTION()
	void OnInteractWithItem();
	
	UFUNCTION()
	void OpenInventory();
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
};
