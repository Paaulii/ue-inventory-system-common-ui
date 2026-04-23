#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "INV_CategoryTabs.generated.h"

class UDynamicEntryBox;
class UINV_CategoryViewModel;
class UINV_InventoryViewModel;
class UINV_SelectionViewModel;
struct FINV_CategoryDefinitionData;

UCLASS()
class INVENTORY_API UINV_CategoryTabs : public UUserWidget
{
	GENERATED_BODY()
private:
	UFUNCTION(BlueprintCallable)
	void VM_CreateTabs(const TArray<UINV_CategoryViewModel*> CategoryViewModels);

	UFUNCTION(BlueprintCallable)
	void ChangeCategory(const int32 Offset) const;

	void CacheViewModels();
	void SelectTab(const int32 Index) const;
	void ResetTabs() const;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDynamicEntryBox> TabButtons = nullptr;

	UPROPERTY()
	TObjectPtr<UINV_InventoryViewModel> CacheInventoryVM = nullptr;
	
	UPROPERTY()
	TObjectPtr<UINV_SelectionViewModel> CacheSelectionVM = nullptr;
};
