// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/MVVM/UIS_ViewModelBase.h"
#include "INV_InventoryViewModel.generated.h"

struct FGameplayTag;
class UINV_ItemActionViewModel;
struct FINV_CategoryDisplayData;
struct FINV_InventoryDisplayData;
class UINV_InventoryComponent;
class UINV_CategoryViewModel;

UCLASS()
class INVENTORY_API UINV_InventoryViewModel : public UUIS_ViewModelBase
{
	GENERATED_BODY()
public:
	virtual void Initialize() override;
	virtual void Deinitialize() override;

	float GetCurrencyAmount() const { return CurrencyAmount; }
	int GetMaxItemsCapacity() const { return MaxItemsCapacity; }
	TArray<UINV_CategoryViewModel*> GetCategories() const { return Categories;}
protected:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Category = "ViewModel")
	float CurrencyAmount;
	
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Category = "ViewModel")
	int MaxItemsCapacity;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Category = "ViewModel")
	TArray<UINV_CategoryViewModel*> Categories;
	
private:
	UFUNCTION()
	void RebuildInventory(const FINV_InventoryDisplayData& InventoryData);
	
	UFUNCTION()
	void UpdateCategoryData(const FINV_CategoryDisplayData& CategoryData);
	
	void ResetCategories();
	void InitializeCategoryVM(const TArray<FINV_CategoryDisplayData>& CategoryDataArray);
	void SetCurrencyAmount(float Value);
	void SetMaxItemsCapacity(int Value);

	UPROPERTY()
	TObjectPtr<UINV_InventoryComponent> InventoryComponent;

	UPROPERTY()
	TObjectPtr<UINV_ItemActionViewModel> CachedPromptVM;
};
