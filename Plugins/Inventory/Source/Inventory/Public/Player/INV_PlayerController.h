// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/UIS_PlayerController.h"
#include "INV_PlayerController.generated.h"

class UGameplayEffect;
class AINV_Character;
class UINV_ItemTracerComponent;
class UINV_InventoryComponent;
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
	AINV_PlayerController();
	
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

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UINV_InventoryComponent> InventoryComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UINV_ItemTracerComponent> ItemTracerComponent;

private:
	UFUNCTION()
	void ApplyEffects(const TArray<TSubclassOf<UGameplayEffect>>& EffectsToApply);

	UFUNCTION()
	void RevokeEffects(const TArray<TSubclassOf<UGameplayEffect>>& EffectsToRevoke);
	
	UPROPERTY()
	TObjectPtr<AINV_Character> InventoryCharacter;
};
