// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UIS_UIManagerSubsystem.h"
#include "UIManagerSubsystem.generated.h"

class USelectionViewModel;
class UInventoryViewModel;
/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UUIManagerSubsystem : public UUIS_UIManagerSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void InitializeViewModels();
	UInventoryViewModel* GetInventoryVM() { return InventoryViewModel; }
	USelectionViewModel* GetSelectionVM() { return SelectionViewModel; }
private:
	UPROPERTY()
	TObjectPtr<UInventoryViewModel> InventoryViewModel = nullptr;

	UPROPERTY()
	TObjectPtr<USelectionViewModel> SelectionViewModel = nullptr;
};
