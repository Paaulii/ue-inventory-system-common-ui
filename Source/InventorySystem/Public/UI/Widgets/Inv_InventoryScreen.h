// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Inv_ActivatableMvvmWidget.h"
#include "Data/DebugInventoryData.h"
#include "Inv_InventoryScreen.generated.h"

class UInventoryViewModel;
struct FInventoryData;
class UCategoryTabs;
class UMVVMView;

UCLASS()
class INVENTORYSYSTEM_API UInv_InventoryScreen : public UInv_ActivatableMvvmWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnActivated() override;
protected:
	virtual void CacheViewModels(UUIManagerSubsystem* UIManager) override;
	virtual void ClearViewModelsCache() override;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget) )
	TObjectPtr<UCategoryTabs> CategoryTabs;
	
	UPROPERTY(EditDefaultsOnly )
	TObjectPtr<UDebugInventoryData> DebugData ;
private:
	UPROPERTY()
	TObjectPtr<UInventoryViewModel> CachedInventoryVM;
	
	bool bIsDataDebugInitialized = false;
};
