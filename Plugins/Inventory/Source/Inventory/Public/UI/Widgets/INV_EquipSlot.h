// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "INV_EquipSlot.generated.h"

class UImage;
class UINV_ItemViewModel;
enum class EINV_ItemEquipType : uint8;
/**
 * 
 */
UCLASS()
class INVENTORY_API UINV_EquipSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	void VM_ItemEquipStateChange(UINV_ItemViewModel* ItemVM);

	UFUNCTION(BlueprintCallable)
	void VM_EquippedItemsChanged(TArray<UINV_ItemViewModel*> EquippedItems);

protected:
	UPROPERTY(EditInstanceOnly, Category="SlotProperties")
	EINV_ItemEquipType EquipType;
	
	UPROPERTY(EditInstanceOnly, Category="SlotProperties")
	UTexture2D* EmptySlotImage;
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Slot;
};
