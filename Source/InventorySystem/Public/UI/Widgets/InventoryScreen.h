// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "InventoryScreen.generated.h"

class UCategoryTabs;
class UMVVMView;

UCLASS()
class INVENTORYSYSTEM_API UInventoryScreen : public UCommonActivatableWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget) )
	TObjectPtr<UCategoryTabs> CategoryTabs;
	
private:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;

	void NotifyChildWidgetsOnActivated() const;
	
	UPROPERTY()
	TObjectPtr<UMVVMView> MVVMView = nullptr;
	

	bool bIsDataDebugInitialized = false;
};
