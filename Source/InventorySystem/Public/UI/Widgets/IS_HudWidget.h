#pragma once

#include "CoreMinimal.h"
#include "UI/MVVM/UIS_MVVMActivatableWidget.h"
#include "IS_HudWidget.generated.h"

UCLASS()
class INVENTORYSYSTEM_API UIS_HudWidget : public UUIS_MVVMActivatableWidget
{
	GENERATED_BODY()

protected:
	virtual void CacheViewModels(UUIS_MVVMUIManagerSubsystem& UIManager, UMVVMView* View) override;
};
