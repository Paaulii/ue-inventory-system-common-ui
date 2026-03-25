// Copyright Paulina Hałatek, All Rights Reserved.


#include "Player/INV_PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Items/INV_Item.h"
#include "Player/INV_Character.h"
#include "Player/Components/INV_ItemTracerComponent.h"
#include "Player/Components/Inventory/INV_InventoryComponent.h"

AINV_PlayerController::AINV_PlayerController()
{
	InventoryComponent = CreateDefaultSubobject<UINV_InventoryComponent>("InventoryComponent");
	ItemTracerComponent = CreateDefaultSubobject<UINV_ItemTracerComponent>("ItemTracer");

	InventoryComponent->OnDelegateApplyEffect.AddDynamic(this, &AINV_PlayerController::ApplyEffects);
}

void AINV_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>((GetLocalPlayer()));

	if (IsValid(Subsystem)) {
		Subsystem->AddMappingContext(DefaultIMC, 0);
	}

	InventoryCharacter = Cast<AINV_Character>(GetCharacter());
	InventoryComponent->LoadInventoryData();
}

void AINV_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AINV_PlayerController::OnInteractWithItem);
	EnhancedInputComponent->BindAction(OpenInventoryAction, ETriggerEvent::Started, this, &AINV_PlayerController::OpenInventory);
}

void AINV_PlayerController::ApplyEffects(const TArray<TSubclassOf<UGameplayEffect>>& EffectsToApply)
{
	if (InventoryCharacter)
	{
		InventoryCharacter->ApplyEffects(EffectsToApply);
	}
}

void AINV_PlayerController::OnInteractWithItem()
{
	UE_LOG(LogTemp, Warning, TEXT("INTERACT"));
	TObjectPtr<AActor> HoveredActor = ItemTracerComponent->GetHoveredActor();
	if (!IsValid(HoveredActor))
	{
		return;
	}

	if (AINV_Item* Item = Cast<AINV_Item>(HoveredActor))
	{
		InventoryComponent->TryAddItem(Item->GetItemDefinition());
		Item->PickUp();
	} 
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