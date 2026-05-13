#pragma once

#include "CoreMinimal.h"
#include "Data/Types/INV_ItemSaveDataTypes.h"
#include "INV_ItemNotificationSystem.generated.h"

class UINV_InventoryComponent;
struct FINV_ItemData;
struct FINV_ItemDisplayData;
struct FINV_ItemIdentification;

UCLASS(Blueprintable)
class INVENTORY_API UINV_ItemNotificationSystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FINV_OnShowNotification, const FINV_ItemDisplayData& ItemDisplayData);
	FINV_OnShowNotification OnShowNotification;

	DECLARE_MULTICAST_DELEGATE_OneParam(FINV_OnHideNotification, const FINV_ItemIdentification& ItemId);
	FINV_OnHideNotification OnHideNotification;
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void PlayerControllerChanged(APlayerController* NewPlayerController) override;
	void OnNotificationHidden(const FINV_ItemIdentification& ItemId);
	
private:
	UFUNCTION()
	void OnItemCollected(FINV_ItemData& ItemData);
	
	UFUNCTION()
	void OnItemDisplayTimeout(const FINV_ItemIdentification ItemId, FTimerHandle TimerHandle);

	void ShowNotification(const FINV_ItemData& ItemData);

	void TryShowNextNotification();
	
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0"))
	int32 MaxNotificationCapacity = 0;

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0"))
	float NotificationDisplayTime = 0.0f;

	UPROPERTY()
	TObjectPtr<UINV_InventoryComponent> InventoryComponent;

	UPROPERTY()
	TArray<FINV_ItemData> NotificationQueue;
	
	UPROPERTY()
	TArray<FINV_ItemData> ActiveNotifications;

	UPROPERTY()
	TArray<FTimerHandle> ActiveTimers = {};
};
