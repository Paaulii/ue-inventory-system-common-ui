// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "INV_ActivatableMvvmWidget.h"
#include "INV_InventoryScreen.generated.h"

class UINV_ItemActionViewModel;
class UINV_SelectionViewModel;
class UINV_InventoryViewModel;

UCLASS()
class INVENTORY_API UINV_InventoryScreen : public UINV_ActivatableMvvmWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
	virtual void CacheViewModels(UUIS_MvvmUIManagerSubsystem* UIManager) override;
	virtual void ClearViewModelsCache() override;
private:
	UPROPERTY()
	TObjectPtr<UINV_InventoryViewModel> CachedInventoryVM;
	
	UPROPERTY()
	TObjectPtr<UINV_SelectionViewModel> CachedSelectionVM;
};
