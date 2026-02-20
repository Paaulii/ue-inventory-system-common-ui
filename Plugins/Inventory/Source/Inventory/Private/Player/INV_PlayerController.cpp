// Copyright Paulina Hałatek, All Rights Reserved.


#include "Player/INV_PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Player/Components/Inventory/INV_InventoryComponent.h"

AINV_PlayerController::AINV_PlayerController()
{
	InventoryComponent = CreateDefaultSubobject<UINV_InventoryComponent>("InventoryComponent");
}

void AINV_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>((GetLocalPlayer()));

	if (IsValid(Subsystem)) {
		Subsystem->AddMappingContext(DefaultIMC, 0);
	}
}

void AINV_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AINV_PlayerController::OnInteractWithItem);
	EnhancedInputComponent->BindAction(OpenInventoryAction, ETriggerEvent::Started, this, &AINV_PlayerController::OpenInventory);
}



void AINV_PlayerController::OnInteractWithItem()
{
	UE_LOG(LogTemp, Warning, TEXT("INTERACT"));
}

void AINV_PlayerController::OpenInventory()
{
	if (InventoryComponent == nullptr)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Open Inventory"));
	
	InventoryComponent->ToggleInventory();
}