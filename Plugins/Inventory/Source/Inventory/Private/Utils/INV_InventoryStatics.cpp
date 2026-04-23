#include "Utils/INV_InventoryStatics.h"
#include "Player/Components/Inventory/INV_InventoryComponent.h"

UINV_InventoryComponent* UINV_InventoryStatics::GetInventoryComponent(const APlayerController* PlayerController)
{
	if (!PlayerController)
	{
		return nullptr;
	}

	return PlayerController->FindComponentByClass<UINV_InventoryComponent>();
}
