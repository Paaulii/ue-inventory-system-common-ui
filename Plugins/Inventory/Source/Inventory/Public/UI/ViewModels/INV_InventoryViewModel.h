// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/MVVM/UIS_ViewModelBase.h"
#include "INV_InventoryViewModel.generated.h"

struct FINV_CategoryData;
struct FINV_InventoryData;
class UINV_CategoryViewModel;

UCLASS()
class INVENTORY_API UINV_InventoryViewModel : public UUIS_ViewModelBase
{
	GENERATED_BODY()
public:
	virtual void Initialize() override;
	virtual void Deinitialize() override;
	void RebuildInventory(const FINV_InventoryData& InventoryData);
	void ResetCategories();
	void InitializeCategoryVM(const TArray<FINV_CategoryData>& CategoryDataArray);
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
	void SetCurrencyAmount(float Value);
	void SetMaxItemsCapacity(int Value);
};
