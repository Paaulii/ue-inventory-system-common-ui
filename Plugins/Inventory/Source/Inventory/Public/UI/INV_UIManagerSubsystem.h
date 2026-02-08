// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UIS_UIManagerSubsystem.h"
#include "INV_UIManagerSubsystem.generated.h"

class UINV_SelectionViewModel;
class UINV_InventoryViewModel;
/**
 * 
 */
UCLASS()
class INVENTORY_API UINV_UIManagerSubsystem : public UUIS_UIManagerSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void InitializeViewModels();
	UINV_InventoryViewModel* GetInventoryVM() { return InventoryViewModel; }
	UINV_SelectionViewModel* GetSelectionVM() { return SelectionViewModel; }
private:
	UPROPERTY()
	TObjectPtr<UINV_InventoryViewModel> InventoryViewModel = nullptr;

	UPROPERTY()
	TObjectPtr<UINV_SelectionViewModel> SelectionViewModel = nullptr;
};
