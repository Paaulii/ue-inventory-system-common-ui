// Copyright Paulina Hałatek, All Rights Reserved.

#include "UI/ViewModels/INV_PromptViewModel.h"
#include "Player/Components/Inventory/INV_InventoryComponent.h"

void UINV_PromptViewModel::Initialize()
{
	Super::Initialize();
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		InventoryComponent = PlayerController->FindComponentByClass<UINV_InventoryComponent>();
	}
}

void UINV_PromptViewModel::SetCurrentPrompt(const FName& Prompt)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(CurrentPrompt, Prompt))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetPromptText);
	}
}

FText UINV_PromptViewModel::GetPromptText() const
{
	if (!InventoryComponent)
	{
		return FText::GetEmpty();
	}

	return InventoryComponent->GetPromptTextById(CurrentPrompt);
}
