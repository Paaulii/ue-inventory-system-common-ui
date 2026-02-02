// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CategoryTabs.generated.h"

class UInventoryViewModel;
class UCategoryViewModel;
class USelectionViewModel;
struct FCategoryData;
class UDynamicEntryBox;
/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UCategoryTabs : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void VM_CreateTabs(const TArray<UCategoryViewModel*> CategoryViewModels);

	UFUNCTION(BlueprintCallable)
	void ChangeCategory(const int Offset) const;

	void SelectTab(const int Index) const;
	void ResetTabs() const;
	void CacheViewModels();
	

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDynamicEntryBox> TabButtons;

	UPROPERTY()
	TObjectPtr<UInventoryViewModel> CacheInventoryVM;
	
	UPROPERTY()
	TObjectPtr<USelectionViewModel> CacheSelectionVM;
};
