#pragma once

#include "CoreMinimal.h"
#include "Data/Types/INV_ItemActionType.h"
#include "UI/MVVM/UIS_ViewModelBase.h"
#include "INV_ItemActionViewModel.generated.h"

class UINV_InventoryComponent;
enum class FINV_ItemActionType : uint8;
struct FINV_ItemIdentification;

UCLASS()
class INVENTORY_API UINV_ItemActionViewModel : public UUIS_ViewModelBase
{
	GENERATED_BODY()
	
public:
	virtual void Initialize() override;
	
	UFUNCTION(BlueprintPure, FieldNotify)
	const FText& VM_GetPromptText() const;
	
	void DelegatePerformAction(const FINV_ItemIdentification& ItemIdentification) const;
	void DelegatePerformAction(const FINV_ItemActionType& ActionType, const FINV_ItemIdentification& ItemIdentification) const;
	void DelegateShowItemActionPopup() const;
	void SetSelectedAction(const FINV_ItemActionType& Action);
	void SetIsSingleItemQuantityAction(bool bState);
	bool GetIsSingleItemQuantityAction() const { return IsSingleItemQuantityAction; };
	const FINV_ItemActionType& GetSelectedAction() const { return SelectedAction; }
	
protected:
	//TODO: Add Quantity
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, Setter)
	FINV_ItemActionType SelectedAction = FINV_ItemActionType::None;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, Setter)
	bool IsSingleItemQuantityAction = false;
	
private:
	UPROPERTY()
	TObjectPtr<UINV_InventoryComponent> InventoryComponent = nullptr;
};
