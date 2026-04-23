#pragma once

#include "CoreMinimal.h"
#include "UI/MVVM/UIS_ViewModelBase.h"
#include "INV_EquipmentViewModel.generated.h"

class UINV_InventoryComponent;
class UINV_ItemViewModel;
struct FINV_ItemIdentification;

UCLASS()
class INVENTORY_API UINV_EquipmentViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()
	
public:
	void OnEquipItem(UINV_ItemViewModel& EquippedItem);
	void OnUnequipItem(UINV_ItemViewModel& UnequippedItem);
	const TArray<UINV_ItemViewModel*>& GetEquippedItems() const { return EquippedItems; }
	const UINV_ItemViewModel* GetLastEquippedItem() const { return LastEquippedItem; }
	const UINV_ItemViewModel* GetLastUnequippedItem() const { return LastUnequippedItem; }
	
protected:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	TArray<UINV_ItemViewModel*> EquippedItems = {};

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	TObjectPtr<UINV_ItemViewModel> LastEquippedItem = nullptr;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	TObjectPtr<UINV_ItemViewModel> LastUnequippedItem = nullptr;
	
private:
	void SetLastEquippedItem(UINV_ItemViewModel* EquippedItem);
	void SetLastUnequippedItem(UINV_ItemViewModel* UnequippedItem);
};
