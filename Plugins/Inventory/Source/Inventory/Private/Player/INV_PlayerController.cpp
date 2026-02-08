// Copyright Paulina Hałatek, All Rights Reserved.


#include "Player/INV_PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

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
	UE_LOG(LogTemp, Warning, TEXT("Open Inventory"));
	
}