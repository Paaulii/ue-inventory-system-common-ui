// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/INV_EquipSlot.h"

#include "Components/Image.h"
#include "UI/ViewModels/INV_ItemViewModel.h"

void UINV_EquipSlot::NativePreConstruct()
{
	Super::NativePreConstruct();

	Image_Slot->SetBrushFromTexture(EmptySlotImage);
}

void UINV_EquipSlot::VM_ItemEquipStateChange(UINV_ItemViewModel* ItemVM)
{
	if (ItemVM == nullptr || ItemVM->GetEquipType() != EquipType )
	{
		return;
	}

	UTexture2D* SlotImage = ItemVM->GetIsEquipped() ? ItemVM->GetSmallImage() : EmptySlotImage;
	Image_Slot->SetBrushFromTexture(SlotImage);
}

void UINV_EquipSlot::VM_EquippedItemsChanged(TArray<UINV_ItemViewModel*> EquippedItems)
{
	for (auto EquippedItem : EquippedItems)
	{
		if (EquippedItem->GetEquipType() == EquipType )
		{
			VM_ItemEquipStateChange(EquippedItem);
			return;
		};
	}
}
