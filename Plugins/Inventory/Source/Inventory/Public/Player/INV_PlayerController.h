#pragma once

#include "Player/UIS_PlayerController.h"
#include "CoreMinimal.h"
#include "INV_PlayerController.generated.h"

class AINV_Character;
class UGameplayEffect;
class UInputAction;
class UInputMappingContext;
class UINV_EquipmentComponent;
class UINV_InventoryComponent;
class UINV_ItemTracerComponent;

UCLASS()
class INVENTORY_API AINV_PlayerController : public AUIS_PlayerController
{
	GENERATED_BODY()

public:
	AINV_PlayerController();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TObjectPtr<UInputMappingContext> DefaultIMC;

	UPROPERTY(EditDefaultsOnly, Category ="Inventory")
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TObjectPtr<UInputAction> OpenInventoryAction;

private:
	virtual void SetupInputComponent() override;
	
	UFUNCTION()
	void OpenInventory();
	
	UFUNCTION()
	void OnInteractWithItem();
	
	UFUNCTION()
	void ApplyEffects(const TArray<TSubclassOf<UGameplayEffect>>& EffectsToApply);

	UFUNCTION()
	void RevokeEffects(const TArray<TSubclassOf<UGameplayEffect>>& EffectsToRevoke);
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UINV_InventoryComponent> InventoryComponent = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UINV_EquipmentComponent> EquipmentComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UINV_ItemTracerComponent> ItemTracerComponent = nullptr;

	UPROPERTY()
	TObjectPtr<AINV_Character> InventoryCharacter = nullptr;
};
