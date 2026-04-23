#pragma once

#include "CoreMinimal.h"
#include "INV_CategoryViewModel.h"
#include "INV_ItemViewModel.h"
#include "UI/MVVM/UIS_ViewModelBase.h"
#include "INV_InventoryViewModel.generated.h"

class UINV_CategoryViewModel;
class UINV_EquipmentViewModel;
class UINV_InventoryComponent;
class UINV_ItemActionViewModel;
class UINV_ItemViewModel;
struct FGameplayTag;
struct FINV_CategoryDisplayData;
struct FINV_InventoryDisplayData;
struct FINV_ItemDisplayData;
struct FINV_ItemIdentification;

UCLASS()
class INVENTORY_API UINV_InventoryViewModel : public UUIS_ViewModelBase
{
	GENERATED_BODY()
	
public:
	virtual void Initialize() override;
	virtual void Deinitialize() override;
	float GetCurrencyAmount() const { return CurrencyAmount; }
	int32 GetMaxItemsCapacity() const { return MaxItemsCapacity; }
	TArray<UINV_CategoryViewModel*> GetCategories() const { return Categories; }
	UINV_EquipmentViewModel* GetEquipment() const { return Equipment; }
	
protected:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Category = "ViewModel")
	float CurrencyAmount = 0.0f;
	
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Category = "ViewModel")
	int32 MaxItemsCapacity = 0;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Category = "ViewModel")
	TArray<UINV_CategoryViewModel*> Categories = {};
	
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter, Category = "ViewModel")
	TObjectPtr<UINV_EquipmentViewModel> Equipment = nullptr;
	
private:
	UFUNCTION()
	void RebuildInventory(const FINV_InventoryDisplayData& InventoryData);
	
	UFUNCTION()
	void UpdateCategoryData(const FINV_CategoryDisplayData& CategoryData);
	
	UFUNCTION()
	void HandleItemEquipped(const FINV_ItemIdentification& ItemIdentification);
	
	UFUNCTION()
	void HandleItemUnequipped(const FINV_ItemIdentification& ItemIdentification);
	
	UFUNCTION()
	void HandleCurrencyChanged(const int32 Value);

	void InitializeCategoryVM(const TArray<FINV_CategoryDisplayData>& CategoryDataArray);
	void SetCurrencyAmount(float Value);
	void SetMaxItemsCapacity(int32 Value);
	void SetEquipment(UINV_EquipmentViewModel* EquipmentVM);
	UINV_ItemViewModel* GetItemById(const FINV_ItemIdentification& ItemIdentification);
	
	UPROPERTY()
	TObjectPtr<UINV_InventoryComponent> InventoryComponent = nullptr;
};

