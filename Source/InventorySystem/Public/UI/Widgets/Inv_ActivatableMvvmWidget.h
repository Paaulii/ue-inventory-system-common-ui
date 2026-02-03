// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Inv_ActivatableMvvmWidget.generated.h"

class UUIManagerSubsystem;
class UMVVMView;
/**
 * 
 */
UCLASS(Abstract)
class INVENTORYSYSTEM_API UInv_ActivatableMvvmWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;
protected:
	virtual void CacheViewModels(UUIManagerSubsystem* UIManager) PURE_VIRTUAL(UInv_ActivatableMvvmWidget::CacheViewModels, );
	virtual void ClearViewModelsCache() PURE_VIRTUAL(UInv_ActivatableMvvmWidget::ClearViewModelsCache, );
	
	UPROPERTY()
	TObjectPtr<UMVVMView> MVVMView;
};
