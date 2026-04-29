#include "Player/INV_PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Items/INV_Item.h"
#include "Player/Components/INV_EquipmentComponent.h"
#include "Player/Components/INV_ItemTracerComponent.h"
#include "Player/Components/Inventory/INV_InventoryComponent.h"
#include "Player/INV_Character.h"

AINV_PlayerController::AINV_PlayerController()
{
	InventoryComponent = CreateDefaultSubobject<UINV_InventoryComponent>(FName("InventoryComponent"));
	EquipmentComponent = CreateDefaultSubobject<UINV_EquipmentComponent>(FName("EquipmentComponent"));
	ItemTracerComponent = CreateDefaultSubobject<UINV_ItemTracerComponent>(FName("ItemTracer"));

	InventoryComponent->OnDelegateApplyEffect.AddDynamic(this, &AINV_PlayerController::ApplyEffects);
	InventoryComponent->OnDelegateRevokeEffect.AddDynamic(this, &AINV_PlayerController::RevokeEffects);
}

void AINV_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>((GetLocalPlayer()));

	if (IsValid(Subsystem))
	{
		Subsystem->AddMappingContext(DefaultIMC, 0);
	}
	
	EquipmentComponent->Initialize(this, nullptr);

	InventoryCharacter = Cast<AINV_Character>(GetCharacter());
	InventoryComponent->LoadInventoryData();
}

void AINV_PlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	if (InventoryComponent)
	{
		InventoryComponent->OnDelegateApplyEffect.RemoveDynamic(this, &AINV_PlayerController::ApplyEffects);
		InventoryComponent->OnDelegateRevokeEffect.RemoveDynamic(this, &AINV_PlayerController::RevokeEffects);
	}

	if (InputComponent)
	{
		InputComponent->ClearActionBindings();
	}
}

void AINV_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AINV_PlayerController::OnInteractWithItem);
	EnhancedInputComponent->BindAction(OpenInventoryAction, ETriggerEvent::Started, this, &AINV_PlayerController::OpenInventory);
}

void AINV_PlayerController::OpenInventory()
{
	TRACE_CPUPROFILER_EVENT_SCOPE(AINV_PlayerController::OpenInventory);
	if (InventoryComponent == nullptr)
	{
		return;
	}
	
	InventoryComponent->ToggleInventory();
}

void AINV_PlayerController::OnInteractWithItem()
{
	TRACE_CPUPROFILER_EVENT_SCOPE(AINV_PlayerController::OnInteractWithItem);
		
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

void AINV_PlayerController::ApplyEffects(const TArray<TSubclassOf<UGameplayEffect>>& EffectsToApply)
{
	if (InventoryCharacter)
	{
		InventoryCharacter->ApplyEffects(EffectsToApply);
	}
}

void AINV_PlayerController::RevokeEffects(const TArray<TSubclassOf<UGameplayEffect>>& EffectsToRevoke)
{
	if (InventoryCharacter)
	{
		InventoryCharacter->RevokeEffects(EffectsToRevoke);
	}
}