// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "INV_ItemActionButton.h"
#include "INV_TwoStateItemActionButton.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UINV_TwoStateItemActionButton : public UINV_ItemActionButton
{
	GENERATED_BODY()
public:
	void ChangeTextByState(bool bState);
protected:
	UPROPERTY(EditInstanceOnly, Category="Label")
	FText SecondStateButtonText;
	
};
