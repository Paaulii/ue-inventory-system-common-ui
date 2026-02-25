// Copyright Paulina Hałatek, All Rights Reserved.


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

void UINV_ItemTracerComponent::TraceForItem()
{
	if (!IsValid(GEngine) || !IsValid(GEngine->GameViewport))
	{
		return;
	}

	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);
	const FVector2D ViewportCenter = ViewportSize / 2.f;

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

	if (ThisActor && ThisActor->Implements<UINV_Highlightable>())
	{
		IINV_Highlightable::Execute_Highlight(ThisActor);
	}

	if (LastActor && LastActor->Implements<UINV_Highlightable>())
	{
		IINV_Highlightable::Execute_UnHighlight(LastActor);
	}
}

void UINV_ItemTracerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TraceForItem();
}

