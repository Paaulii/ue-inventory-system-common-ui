// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "INV_ActivatableMvvmWidget.generated.h"

class UUIS_MvvmUIManagerSubsystem;
class UMVVMView;
/**
 * 
 */
UCLASS(Abstract)
class INVENTORY_API UINV_ActivatableMvvmWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
protected:
	virtual void CacheViewModels(UUIS_MvvmUIManagerSubsystem* UIManager) PURE_VIRTUAL(UInv_ActivatableMvvmWidget::CacheViewModels, );
	virtual void ClearViewModelsCache() PURE_VIRTUAL(UInv_ActivatableMvvmWidget::ClearViewModelsCache, );
	
	UPROPERTY()
	TObjectPtr<UMVVMView> MVVMView;
};
