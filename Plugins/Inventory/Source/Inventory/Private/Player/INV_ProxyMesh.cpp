#include "Player/INV_ProxyMesh.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Player/Components/INV_EquipmentComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"

AINV_ProxyMesh::AINV_ProxyMesh()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("Root"));

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	EquipmentComponent = CreateDefaultSubobject<UINV_EquipmentComponent>(FName("Equipment"));
	EquipmentComponent->OnItemAttached.AddDynamic(this, &ThisClass::OnItemAttached);
	EquipmentComponent->OnItemDetached.AddDynamic(this, &ThisClass::OnItemDetached);
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(FName("SceneCapture"));
	SceneCaptureComponent->SetupAttachment(SpringArmComponent);
}

void AINV_ProxyMesh::BeginPlay()
{
	Super::BeginPlay();

	SceneCaptureComponent->ShowOnlyActors.Add(this);
	WaitForPawnPossession();
}

void AINV_ProxyMesh::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (UWorld* World = GetWorld())
	{
		if (APlayerController* Controller = World->GetFirstPlayerController())
		{
			Controller->OnPossessedPawnChanged.RemoveDynamic(this, &AINV_ProxyMesh::SetupMesh);
		}
	}

	if (EquipmentComponent)
	{
		EquipmentComponent->OnItemAttached.RemoveDynamic(this, &ThisClass::OnItemAttached);
		EquipmentComponent->OnItemDetached.RemoveDynamic(this, &ThisClass::OnItemDetached);
	}
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
