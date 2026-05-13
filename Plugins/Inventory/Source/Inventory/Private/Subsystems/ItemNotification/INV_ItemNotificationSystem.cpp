#include "Subsystems/ItemNotification/INV_ItemNotificationSystem.h"
#include "Player/Components/Inventory/INV_InventoryComponent.h"
#include "TimerManager.h"

void UINV_ItemNotificationSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	ActiveNotifications.Reserve(MaxNotificationCapacity);
}

bool UINV_ItemNotificationSystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return GetClass()->IsInBlueprint() && Super::ShouldCreateSubsystem(Outer);
}

void UINV_ItemNotificationSystem::PlayerControllerChanged(APlayerController* NewPlayerController)
{
	Super::PlayerControllerChanged(NewPlayerController);

	if (NewPlayerController)
	{
		InventoryComponent = NewPlayerController->FindComponentByClass<UINV_InventoryComponent>();
		checkf(InventoryComponent, TEXT("PlayerController doesn't contain InventoryComponent! Make sure to add that component otherwise Item Notification System won't work."));

		InventoryComponent->OnItemCollected.BindUObject(this, &UINV_ItemNotificationSystem::OnItemCollected);
	}
}

void UINV_ItemNotificationSystem::OnItemCollected(FINV_ItemData& ItemData)
{
	if (ActiveNotifications.Num() >= MaxNotificationCapacity)
	{
		NotificationQueue.Add(ItemData);
		return;
	}

	ShowNotification(ItemData);
}

void UINV_ItemNotificationSystem::TryShowNextNotification()
{
	if (NotificationQueue.Num() <= 0)
	{
		return;
	}
	
	ShowNotification(NotificationQueue.Pop());
}

void UINV_ItemNotificationSystem::ShowNotification(const FINV_ItemData& ItemData)
{
	if (UWorld* World = GetWorld())
	{
		if (FTimerManager* TimerManager = &World->GetTimerManager())
		{
			FTimerHandle ItemDisplayTimerHandle;
			FTimerDelegate TimeDisplayTimeoutDelegate = FTimerDelegate::CreateUObject(this, &UINV_ItemNotificationSystem::OnItemDisplayTimeout, ItemData.ItemIdentification, ItemDisplayTimerHandle);
			TimerManager->SetTimer(ItemDisplayTimerHandle, TimeDisplayTimeoutDelegate, NotificationDisplayTime, false);
			ActiveTimers.Add(ItemDisplayTimerHandle);
		}
	}
	
	ActiveNotifications.Add(ItemData);

	TOptional<FINV_ItemDisplayData> ItemDisplayData = InventoryComponent->CreateItemDisplayData(ItemData);

	if (!ItemDisplayData.IsSet())
	{
		return;
	}
	
	OnShowNotification.Broadcast(ItemDisplayData.GetValue());
}

void UINV_ItemNotificationSystem::OnItemDisplayTimeout(const FINV_ItemIdentification ItemId, FTimerHandle TimerHandle)
{
	ActiveTimers.RemoveAll([TimerHandle](const FTimerHandle& Handle)
	{
		return Handle == TimerHandle;
	});

	OnHideNotification.Broadcast(ItemId);
}

void UINV_ItemNotificationSystem::OnNotificationHidden(const FINV_ItemIdentification& HiddenItemId)
{
	ActiveNotifications.RemoveAll([HiddenItemId](const FINV_ItemData& ItemData)
	{
		return ItemData.ItemIdentification == HiddenItemId;
	});

	TryShowNextNotification();
}




