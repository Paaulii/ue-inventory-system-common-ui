// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/MVVM/UIS_ViewModelBase.h"
#include "INV_PromptViewModel.generated.h"

class UINV_InventoryComponent;
UCLASS()
class INVENTORY_API UINV_PromptViewModel : public UUIS_ViewModelBase
{
	GENERATED_BODY()
public:
	virtual void Initialize() override;
	
	FName GetCurrentPrompt() const {return CurrentPrompt;}
	void SetCurrentPrompt(const FName& Prompt);

	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetPromptText() const;
protected:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, Setter)
	FName CurrentPrompt;
private:
	UPROPERTY()
	TObjectPtr<UINV_InventoryComponent> InventoryComponent;
};
