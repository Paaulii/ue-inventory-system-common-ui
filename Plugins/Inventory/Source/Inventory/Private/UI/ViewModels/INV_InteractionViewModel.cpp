#include "UI/ViewModels/INV_InteractionViewModel.h"
#include "Player/Components/INV_ItemTracerComponent.h"

void UINV_InteractionViewModel::Initialize()
{
	Super::Initialize();
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		ItemTracerComponent = PlayerController->FindComponentByClass<UINV_ItemTracerComponent>();
		checkf(ItemTracerComponent, TEXT("PlayerController doesn't contain ItemTracerComponent! Make sure to add that component otherwise Inventory System won't work."));
		ItemTracerComponent->OnItemHoverStateChanged.AddUObject(this, &UINV_InteractionViewModel::SetbIsItemHovered);
	}
}

void UINV_InteractionViewModel::Deinitialize()
{
	if (ItemTracerComponent)
	{
		ItemTracerComponent->OnItemHoverStateChanged.RemoveAll(this);
	}
}

void UINV_InteractionViewModel::SetbIsItemHovered(bool bState)
{
	UE_MVVM_SET_PROPERTY_VALUE(bIsItemHovered, bState);
}
