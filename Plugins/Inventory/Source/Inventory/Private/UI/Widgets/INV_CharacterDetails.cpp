#include "UI/Widgets/INV_CharacterDetails.h"
#include "UI/Widgets/INV_EquipSlot.h"
#include "Blueprint/WidgetTree.h"
#include "UI/ViewModels/INV_ItemViewModel.h"

void UINV_CharacterDetails::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	GetEquipSlotWidgets();
}

void UINV_CharacterDetails::GetEquipSlotWidgets()
{
	EquipSlotItems.Empty();
	TArray<UWidget*> Widgets;
	WidgetTree->GetAllWidgets(Widgets);

	for (const auto Widget : Widgets)
	{
		if (UINV_EquipSlot* EquipSlot = Cast<UINV_EquipSlot>(Widget))
		{
			EquipSlotItems.Add(EquipSlot);
		}
	}
}

void UINV_CharacterDetails::VM_LastItemEquipStateChanged(UINV_ItemViewModel* Item)
{
	if (!Item)
	{
		return;
	}
	
	for (const auto& EquippedItem : EquipSlotItems)
	{
		if (EquippedItem->GetEquipType() == Item->GetEquipType())
		{
			EquippedItem->SetEquipSlotImage(Item);
			return;
		}
	}
}

void UINV_CharacterDetails::VM_EquippedItemsChanged(TArray<UINV_ItemViewModel*> EquippedItems)
{
	for (const auto& EquippedItem : EquippedItems)
	{
		VM_LastItemEquipStateChanged(EquippedItem);
	}
}