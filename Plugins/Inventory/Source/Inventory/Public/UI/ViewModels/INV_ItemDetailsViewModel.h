// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/MVVM/UIS_ViewModelBase.h"
#include "INV_ItemDetailsViewModel.generated.h"

class UINV_InventoryComponent;
/**
 * 
 */
UCLASS()
class INVENTORY_API UINV_ItemDetailsViewModel : public UUIS_ViewModelBase
{
	GENERATED_BODY()
public:
	virtual void Initialize() override;
	
	void OnDropButtonSelected() const;
	void OnConsumeButtonSelected();
	void OnEquipButtonSelected();
private:
	UPROPERTY()
	TObjectPtr<UINV_InventoryComponent> InventoryComponent;
};
