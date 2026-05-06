#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "INV_CharacterDetails.generated.h"

class UINV_EquipSlot;
class UINV_ItemViewModel;

UCLASS()
class INVENTORY_API UINV_CharacterDetails : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;
	
protected:
	UFUNCTION(BlueprintCallable)
	void VM_LastItemEquipStateChanged(UINV_ItemViewModel* LastUnequippedItem);

	UFUNCTION(BlueprintCallable)
	void VM_EquippedItemsChanged(TArray<UINV_ItemViewModel*> EquippedItems);

private:
	void GetEquipSlotWidgets();

	TArray<TObjectPtr<UINV_EquipSlot>> EquipSlotItems;
};
