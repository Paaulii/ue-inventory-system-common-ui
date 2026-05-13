#pragma once

#include "CommonActivatableWidget.h"
#include "CoreMinimal.h"
#include "UIS_ViewModelCacher.h"
#include "UIS_MVVMActivatableWidget.generated.h"

class UUIS_MVVMUIManagerSubsystem;
class UMVVMView;

UCLASS(Abstract)
class UISYSTEM_API UUIS_MVVMActivatableWidget : public UCommonActivatableWidget, public UIS_ViewModelCacher
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;
	
protected:
	virtual void CacheViewModels(UUIS_MVVMUIManagerSubsystem& UIManager, UMVVMView* View) override;
	
	UPROPERTY()
	TObjectPtr<UMVVMView> MVVMView = nullptr;
};
