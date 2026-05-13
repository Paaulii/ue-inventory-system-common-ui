#pragma once

#include "CoreMinimal.h"
#include "UI/MVVM/UIS_MVVMActivatableWidget.h"
#include "INV_InventoryScreen.generated.h"

class UINV_InventoryViewModel;
class UINV_ItemActionViewModel;
class UINV_PlayerStatViewModel;
class UINV_SelectionViewModel;

UCLASS()
class INVENTORY_API UINV_InventoryScreen : public UUIS_MVVMActivatableWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnActivated() override;
	virtual void CacheViewModels(UUIS_MVVMUIManagerSubsystem& UIManager, UMVVMView* View) override;
private:
	UPROPERTY()
	TObjectPtr<UINV_InventoryViewModel> CachedInventoryVM = nullptr;
	
	UPROPERTY()
	TObjectPtr<UINV_SelectionViewModel> CachedSelectionVM = nullptr;

	UPROPERTY()
	TObjectPtr<UINV_PlayerStatViewModel> CachedPlayerStatVM = nullptr;
};
