// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/INV_ActivatableMvvmWidget.h"
#include "IS_HudWidget.generated.h"

class UINV_PlayerStatViewModel;
/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UIS_HudWidget : public UINV_ActivatableMvvmWidget
{
	GENERATED_BODY()
protected:
	virtual void CacheViewModels(UUIS_MvvmUIManagerSubsystem* UIManager) override;
	virtual void ClearViewModelsCache() override;
private:
	UPROPERTY()
	TObjectPtr<UINV_PlayerStatViewModel> CachedPlayerStatVM;
	
};
