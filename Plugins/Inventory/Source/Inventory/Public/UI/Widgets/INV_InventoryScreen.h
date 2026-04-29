#pragma once

#include "CoreMinimal.h"
#include "INV_ActivatableMvvmWidget.h"
#include "INV_InventoryScreen.generated.h"

class UINV_InventoryViewModel;
class UINV_ItemActionViewModel;
class UINV_PlayerStatViewModel;
class UINV_SelectionViewModel;

UCLASS()
class INVENTORY_API UINV_InventoryScreen : public UINV_ActivatableMvvmWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnActivated() override;
	//virtual void NativeOnDeactivated() override;
	virtual void CacheViewModels(UUIS_MvvmUIManagerSubsystem& UIManager) override;
private:
	UPROPERTY()
	TObjectPtr<UINV_InventoryViewModel> CachedInventoryVM = nullptr;
	
	UPROPERTY()
	TObjectPtr<UINV_SelectionViewModel> CachedSelectionVM = nullptr;

	UPROPERTY()
	TObjectPtr<UINV_PlayerStatViewModel> CachedPlayerStatVM = nullptr;
};
