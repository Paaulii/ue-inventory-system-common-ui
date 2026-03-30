// Copyright Paulina Hałatek, All Rights Reserved.


#include "Player/INV_ProxyMesh.h"

#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/INV_PlayerController.h"
#include "Player/Components/INV_EquipmentComponent.h"


AINV_ProxyMesh::AINV_ProxyMesh()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	EquipmentComponent = CreateDefaultSubobject<UINV_EquipmentComponent>("Equipment");
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(RootComponent);

	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>("SceneCapture");
	SceneCaptureComponent->SetupAttachment(SpringArmComponent);
}

void AINV_ProxyMesh::BeginPlay()
{
	Super::BeginPlay();

	SceneCaptureComponent->ShowOnlyActors.Add(this);
	WaitForPawnPossession();
}

void AINV_ProxyMesh::WaitForPawnPossession()
{
	if (UWorld* World = GetWorld())
	{
		if (APlayerController* Controller = World->GetFirstPlayerController())
		{
			if (APawn* Pawn = Controller->GetPawn())
			{
				SetupMesh(nullptr, Pawn);
			}
			else
			{
				Controller->OnPossessedPawnChanged.AddDynamic(this, &AINV_ProxyMesh::SetupMesh);
			}
		}
	}
}

void AINV_ProxyMesh::SetupMesh(APawn* OldPawn, APawn* NewPawn)
{
	if (ACharacter* Character = Cast<ACharacter>(NewPawn))
	{
		if (USkeletalMeshComponent* CharacterMesh = Character->GetMesh())
		{
			SourceMesh = CharacterMesh;
			Mesh->SetSkeletalMesh(SourceMesh->GetSkeletalMeshAsset());
			Mesh->SetAnimInstanceClass(SourceMesh->GetAnimInstance()->GetClass());
			EquipmentComponent->SetOwningMesh(Mesh);
			EquipmentComponent->Initialize(Cast<APlayerController>(NewPawn->GetController()), Mesh);
			EquipmentComponent->OnItemAttached.AddDynamic(this, &ThisClass::OnItemAttached);
			EquipmentComponent->OnItemDetached.AddDynamic(this, &ThisClass::OnItemDetached);
		}
	}
}

void AINV_ProxyMesh::OnItemAttached(AActor* AttachedItem)
{
	SceneCaptureComponent->ShowOnlyActors.Add(AttachedItem);
}

void AINV_ProxyMesh::OnItemDetached(AActor* DetachedItem)
{
	SceneCaptureComponent->ShowOnlyActors.Remove(DetachedItem);
}
