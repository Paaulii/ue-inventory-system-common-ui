// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "INV_InventoryComponent.generated.h"


class UINV_InventoryScreen;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class INVENTORY_API UINV_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void ToggleInventory();

protected:
	virtual void BeginPlay() override;

private:
	void SetInventoryVisible(bool bIsVisible);
	void RequestShowInventory();

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<UINV_InventoryScreen> InventoryClass;

	TWeakObjectPtr<APlayerController> OwningController;

	bool bIsBindToInventoryOnDeactivated;
	bool bInventoryMenuOpen;
};
