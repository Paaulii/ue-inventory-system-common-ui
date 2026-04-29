#pragma once

#include "CommonActivatableWidget.h"
#include "CoreMinimal.h"
#include "INV_ActivatableMvvmWidget.generated.h"

class UUIS_MvvmUIManagerSubsystem;
class UMVVMView;

UCLASS(Abstract)
class INVENTORY_API UINV_ActivatableMvvmWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnActivated() override;
protected:
	virtual void CacheViewModels(UUIS_MvvmUIManagerSubsystem& UIManager) PURE_VIRTUAL(UInv_ActivatableMvvmWidget::CacheViewModels, );
	
	UPROPERTY()
	TObjectPtr<UMVVMView> MVVMView = nullptr;
};
