// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "INV_CategoryViewModel.h"
#include "INV_ItemViewModel.h"
#include "UI/MVVM/UIS_ViewModelBase.h"
#include "INV_InventoryViewModel.generated.h"

class UINV_ItemViewModel;
struct FINV_ItemIdentification;
class UINV_EquipmentViewModel;
struct FINV_ItemDisplayData;
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
	UINV_EquipmentViewModel* GetEquipment() const { return Equipment;}
protected:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Category = "ViewModel")
	float CurrencyAmount;
	
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Category = "ViewModel")
	int MaxItemsCapacity;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Category = "ViewModel")
	TArray<UINV_CategoryViewModel*> Categories;
	
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Category = "ViewModel")
	TObjectPtr<UINV_EquipmentViewModel> Equipment;
	
private:
	UFUNCTION()
	void RebuildInventory(const FINV_InventoryDisplayData& InventoryData);
	
	UFUNCTION()
	void UpdateCategoryData(const FINV_CategoryDisplayData& CategoryData);
	
	UFUNCTION()
	void HandleItemEquipped(const FINV_ItemIdentification& ItemIdentification);
	
	UFUNCTION()
	void HandleItemUnequipped(const FINV_ItemIdentification& ItemIdentification);

	void ResetCategories();
	void InitializeCategoryVM(const TArray<FINV_CategoryDisplayData>& CategoryDataArray);
	void SetCurrencyAmount(float Value);
	void SetMaxItemsCapacity(int Value);
	void SetEquipment(UINV_EquipmentViewModel* EquipmentVM);
	UINV_ItemViewModel* GetItemById(const FINV_ItemIdentification& ItemIdentification);
	
	UPROPERTY()
	TObjectPtr<UINV_InventoryComponent> InventoryComponent;
};

