// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Data/DebugInventoryData.h"
#include "InventoryScreen.generated.h"

struct FInventoryData;
class UCategoryTabs;
class UMVVMView;

UCLASS()
class INVENTORYSYSTEM_API UInventoryScreen : public UCommonActivatableWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget) )
	TObjectPtr<UCategoryTabs> CategoryTabs;
	
	UPROPERTY(EditDefaultsOnly )
	TObjectPtr<UDebugInventoryData> DebugData ;
	
private:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;

	UPROPERTY()
	TObjectPtr<UMVVMView> MVVMView = nullptr;
	

	bool bIsDataDebugInitialized = false;
};
