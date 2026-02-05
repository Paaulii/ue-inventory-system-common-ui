// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "Inv_InputAction.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UInv_InputAction : public UCommonButtonBase
{
	GENERATED_BODY()
public:
	virtual void NativePreConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void UpdateTriggeringInputAction(const FDataTableRowHandle& InputAction);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTriggered);
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnTriggered OnTriggered;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Input")
	FDataTableRowHandle CustomInputAction;
protected:
	virtual void HandleTriggeringActionCommited() override;
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonActionWidget> InputAction_CustomAction;
	
};
