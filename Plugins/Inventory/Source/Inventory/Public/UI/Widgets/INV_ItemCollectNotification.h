#pragma once

#include "CoreMinimal.h"
#include "UI/MVVM/UIS_MVVMUserWidget.h"
#include "INV_ItemCollectNotification.generated.h"

class UINV_ItemViewModel;
class UDynamicEntryBox;
class UINV_ItemCollectNotificationEntity;
class UINV_ItemNotificationViewModel;

UCLASS()
class INVENTORY_API UINV_ItemCollectNotification : public UUIS_MVVMUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void CacheViewModels(UUIS_MVVMUIManagerSubsystem& UIManager, UMVVMView* View) override;

	UFUNCTION(BlueprintCallable)
	void VM_OnItemShow(UINV_ItemViewModel* ItemViewModel);
	
	UFUNCTION(BlueprintCallable)
	void VM_OnItemHide(UINV_ItemViewModel* ItemViewModel);
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDynamicEntryBox> ItemNotificationDynamicEntryBox;
	
	UPROPERTY()
	TObjectPtr<UINV_ItemNotificationViewModel> CachedItemNotificationVM;

	UPROPERTY()
	TArray<UINV_ItemCollectNotificationEntity*> ActiveNotifications;
};
