// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "INV_CategoryTabs.generated.h"

class UINV_InventoryViewModel;
class UINV_CategoryViewModel;
class UINV_SelectionViewModel;
struct FINV_CategoryData;
class UDynamicEntryBox;
/**
 * 
 */
UCLASS()
class INVENTORY_API UINV_CategoryTabs : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void VM_CreateTabs(const TArray<UINV_CategoryViewModel*> CategoryViewModels);

	UFUNCTION(BlueprintCallable)
	void ChangeCategory(const int Offset) const;

	void SelectTab(const int Index) const;
	void ResetTabs() const;
	void CacheViewModels();
	

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDynamicEntryBox> TabButtons;

	UPROPERTY()
	TObjectPtr<UINV_InventoryViewModel> CacheInventoryVM;
	
	UPROPERTY()
	TObjectPtr<UINV_SelectionViewModel> CacheSelectionVM;
};
