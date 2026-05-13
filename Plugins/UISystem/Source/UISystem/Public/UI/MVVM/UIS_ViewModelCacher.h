#pragma once

#include "CoreMinimal.h"

class UMVVMView;
class UUIS_MVVMUIManagerSubsystem;

class UISYSTEM_API UIS_ViewModelCacher
{
public:
	void Initialize(const UUserWidget* UserWidgetContext);
	
protected:
	virtual void CacheViewModels(UUIS_MVVMUIManagerSubsystem& UIManager, UMVVMView* View) = 0; 
};
