#include "Player/Components/INV_ItemTracerComponent.h"
#include "Items/Interaction/INV_Highlightable.h"
#include "Kismet/GameplayStatics.h"
#include "Player/INV_PlayerController.h"

UINV_ItemTracerComponent::UINV_ItemTracerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UINV_ItemTracerComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = Cast<AINV_PlayerController>(GetOwner());
}

void UINV_ItemTracerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TraceForItem();
}

void UINV_ItemTracerComponent::TraceForItem()
{
	if (!IsValid(GEngine) || !IsValid(GEngine->GameViewport))
	{
		return;
	}

	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);
	const FVector2D ViewportCenter = ViewportSize / 2.0f;

	FVector TraceStart;
	FVector Forward;

	if (!UGameplayStatics::DeprojectScreenToWorld(Owner, ViewportCenter, TraceStart, Forward))
	{
		return;
	}

	const FVector TraceEnd = TraceStart + Forward * TraceLength;
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ItemTraceChannel);

	LastActor = ThisActor;
	ThisActor = HitResult.GetActor();
	

	if (ThisActor == LastActor)
	{
		return;
	}
	
	if (IINV_Highlightable* LastHighlightedItem = Cast<IINV_Highlightable>(LastActor))
	{
		LastHighlightedItem->Unhighlight();
		OnItemHoverStateChanged.Broadcast(false);
	}
	
	if (IINV_Highlightable* ItemToHighlight = Cast<IINV_Highlightable>(ThisActor))
	{
		ItemToHighlight->Highlight();
		OnItemHoverStateChanged.Broadcast(true);
	}
}