// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/MVVM/UIS_ViewModelBase.h"
#include "INV_ItemActionViewModel.generated.h"

struct FINV_ItemIdentification;
enum class FINV_ItemActionType : uint8;
class UINV_InventoryComponent;
UCLASS()
class INVENTORY_API UINV_ItemActionViewModel : public UUIS_ViewModelBase
{
	GENERATED_BODY()
public:
	virtual void Initialize() override;
	
	UFUNCTION(BlueprintPure, FieldNotify)
	FText GetPromptText() const;
	
	void DelegatePerformAction(const FINV_ItemActionType& ActionType, const FINV_ItemIdentification& ItemIdentification, const int16 SaveDataIndex) const;
	void DelegatePerformAction(const FINV_ItemIdentification& ItemIdentification, const int16 SaveDataIndex) const;
	FINV_ItemActionType GetSelectedAction() const {return SelectedAction;}
	bool GetIsSingleItemQuantityAction() const {return IsSingleItemQuantityAction;};
	void SetSelectedAction(const FINV_ItemActionType& Action);
	void SetIsSingleItemQuantityAction(bool bState);
	void DelegateShowItemActionPopup() const;
protected:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, Setter)
	FINV_ItemActionType SelectedAction;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, Setter)
	bool IsSingleItemQuantityAction;
private:
	UPROPERTY()
	TObjectPtr<UINV_InventoryComponent> InventoryComponent;
};
