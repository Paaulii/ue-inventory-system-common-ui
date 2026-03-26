// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/Widgets/INV_EquipSlot.h"

#include "Components/Image.h"
#include "UI/ViewModels/INV_ItemViewModel.h"

void UINV_EquipSlot::NativePreConstruct()
{
	Super::NativePreConstruct();

	Image_Slot->SetBrushFromTexture(EmptySlotImage);
}

void UINV_EquipSlot::VM_SetSlotImage(UINV_ItemViewModel* ItemVM)
{
	if (ItemVM == nullptr )
	{
		return;
	}

	bool bMatchEquipType =  ItemVM->GetEquipType() == EquipType;

	Image_Slot->SetBrushFromTexture(bMatchEquipType && ItemVM->GetIsEquipped() ? ItemVM->GetSmallImage() : EmptySlotImage);
}
