#pragma once

#include "CommonButtonBase.h"
#include "CoreMinimal.h"
#include "INV_InputAction.generated.h"

UCLASS()
class INVENTORY_API UINV_InputAction : public UCommonButtonBase
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void UpdateTriggeringInputAction(const FDataTableRowHandle& InputAction);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FINV_OnTriggered);
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FINV_OnTriggered OnTriggered;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom Input")
	FDataTableRowHandle CustomInputAction = {};
	
protected:
	virtual void HandleTriggeringActionCommited() override;

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonActionWidget> InputAction_CustomAction = nullptr;
};
