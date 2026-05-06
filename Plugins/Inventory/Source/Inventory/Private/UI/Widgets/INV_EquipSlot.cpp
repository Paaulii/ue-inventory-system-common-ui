#include "UI/Widgets/INV_EquipSlot.h"
#include "Components/Image.h"
#include "UI/ViewModels/INV_ItemViewModel.h"

void UINV_EquipSlot::NativePreConstruct()
{
	Super::NativePreConstruct();
	ImageSlot->SetBrushFromTexture(EmptySlotImage);
}

void UINV_EquipSlot::VM_EquippedItemsChanged(const TArray<UINV_ItemViewModel*>& EquippedItems)
{
	for (const auto& EquippedItem : EquippedItems)
	{
		if (EquippedItem->GetEquipType() == EquipType)
		{
			SetEquipSlotImage(EquippedItem);
			return;
		}
	}
}

void UINV_EquipSlot::SetEquipSlotImage(const UINV_ItemViewModel* ItemVM)
{
	if (ItemVM == nullptr || ItemVM->GetEquipType() != EquipType )
	{
		return;
	}

	UTexture2D* SlotImage = ItemVM->GetbIsEquipped() ? ItemVM->GetSmallImage() : EmptySlotImage;
	ImageSlot->SetBrushFromTexture(SlotImage);
}
