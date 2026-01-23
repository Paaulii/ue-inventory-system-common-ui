// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "InventoryScreen.generated.h"

class UMVVMView;

UCLASS()
class INVENTORYSYSTEM_API UInventoryScreen : public UCommonActivatableWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;

	UMVVMView* MVVMView = nullptr;
};
