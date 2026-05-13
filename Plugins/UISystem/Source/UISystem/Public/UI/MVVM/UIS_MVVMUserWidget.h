#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/MVVM/UIS_ViewModelCacher.h"
#include "UIS_MVVMUserWidget.generated.h"

class UMVVMView;
class UUIS_MVVMUIManagerSubsystem;

UCLASS()
class UISYSTEM_API UUIS_MVVMUserWidget : public UUserWidget, public UIS_ViewModelCacher
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;
	
protected:
	virtual void CacheViewModels(UUIS_MVVMUIManagerSubsystem& UIManager, UMVVMView* View) override;
	
	UPROPERTY()
	TObjectPtr<UMVVMView> MVVMView = nullptr;
};
