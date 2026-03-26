// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "INV_ActivatableMvvmWidget.h"
#include "INV_CharacterDetails.generated.h"

class UINV_PlayerStatViewModel;
/**
 * 
 */
UCLASS()
class INVENTORY_API UINV_CharacterDetails : public UINV_ActivatableMvvmWidget
{
	GENERATED_BODY()

protected:
	virtual void CacheViewModels(UUIS_MvvmUIManagerSubsystem* UIManager);
	virtual void ClearViewModelsCache();

	UPROPERTY()
	TObjectPtr<UINV_PlayerStatViewModel> CachedPlayerStatVM;
};
