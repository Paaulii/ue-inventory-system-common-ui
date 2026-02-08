// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "INV_ActivatableMvvmWidget.h"
#include "Data/INV_DebugInventoryData.h"
#include "INV_InventoryScreen.generated.h"

class UINV_SelectionViewModel;
class UINV_InventoryViewModel;
struct FINV_InventoryData;
class UINV_CategoryTabs;
class UMVVMView;

UCLASS()
class INVENTORY_API UINV_InventoryScreen : public UINV_ActivatableMvvmWidget
{
	GENERATED_BODY()
public:
	DECLARE_MULTICAST_DELEGATE(FOnInventory)
	virtual void NativeOnActivated() override;
	
protected:
	virtual void CacheViewModels(UINV_UIManagerSubsystem* UIManager) override;
	virtual void ClearViewModelsCache() override;
	
	UPROPERTY(EditDefaultsOnly )
	TObjectPtr<UINV_DebugInventoryData> DebugData ;
private:
	UPROPERTY()
	TObjectPtr<UINV_InventoryViewModel> CachedInventoryVM;
	
	UPROPERTY()
	TObjectPtr<UINV_SelectionViewModel> CachedSelectionVM;
	
	bool bIsDataDebugInitialized = false;
};
