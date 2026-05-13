#pragma once

#include "CoreMinimal.h"
#include "UI/MVVM/UIS_ViewModelBase.h"
#include "INV_ItemNotificationViewModel.generated.h"

class UINV_ItemNotificationSystem;
class UINV_ItemViewModel;
struct FINV_ItemDisplayData;
struct FINV_ItemIdentification;

UCLASS()
class INVENTORY_API UINV_ItemNotificationViewModel : public UUIS_ViewModelBase
{
	GENERATED_BODY()
	
public:
	virtual void Initialize() override;
	virtual void Deinitialize() override;
	
	const UINV_ItemViewModel* GetItemToShow() const { return ItemToShow; }
	const UINV_ItemViewModel* GetItemToHide() const { return ItemToHide; }
	void OnItemNotificationHidden(const UINV_ItemViewModel* ItemVM) const;
	
protected:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	TObjectPtr<UINV_ItemViewModel> ItemToShow = nullptr;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	TObjectPtr<UINV_ItemViewModel> ItemToHide = nullptr;

private:
	UFUNCTION()
	void OnShowItemNotification(const FINV_ItemDisplayData& ItemDisplayData);
	
	UFUNCTION()
	void OnHideItemNotification(const FINV_ItemIdentification& ItemId);

	UINV_ItemViewModel* PopulateItemVM(const FINV_ItemDisplayData& ItemDisplayData);
	
	UPROPERTY()
	TObjectPtr<UINV_ItemNotificationSystem> ItemNotificationSystem;

	UPROPERTY()
	TArray<UINV_ItemViewModel*> ActiveNotifications;
};
