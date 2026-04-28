#pragma once

#include "CoreMinimal.h"
#include "Data/Types/INV_ItemEquipType.h"
#include "Data/Types/INV_ItemRarity.h"
#include "Data/Types/INV_ItemSaveDataTypes.h"
#include "INV_CategoryViewModel.h"
#include "MVVMViewModelBase.h"
#include "INV_ItemViewModel.generated.h"

enum class EINV_ItemEquipType : uint8;

UCLASS()
class INVENTORY_API UINV_ItemViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, FieldNotify)
	bool VM_IsQuantityVisible() const;
	
	UFUNCTION(BlueprintPure, FieldNotify)
	bool VM_IsSingleItem() const;
	
	void Initialize(const FINV_ItemDisplayData& ItemData, UINV_CategoryViewModel* CategoryVM);
	void SetbIsEquipped(bool bState);
	const FText& GetItemName() const { return ItemName; }
	const FText& GetDescription() const { return Description; }
	const EINV_ItemRarity& GetRarity() const { return Rarity; }
	UINV_CategoryViewModel* GetCategory() const { return Category; }
	const EINV_ItemEquipType& GetEquipType() const { return EquipType; }
	const FINV_ItemIdentification& GetItemIdentification() const { return ItemIdentification; }
	UTexture2D* GetSmallImage() const { return SmallImage; }
	UTexture2D* GetLargeImage() const { return LargeImage; }
	int32 GetCurrencyValue() const { return CurrencyValue; }
	int32 GetRequiredLevel() const { return RequiredLevel; }
	int32 GetQuantity() const { return Quantity; }
	int32 GetMaxQuantity() const { return MaxQuantity; }
	bool GetbIsEquippable() const { return bIsEquippable; }
	bool GetbIsConsumable() const { return bIsConsumable; }
	bool GetbIsDroppable() const { return bIsDroppable; }
	bool GetbIsEquipped() const { return bIsEquipped; }
	
protected:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	FText ItemName = {};
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	FText Description = {};

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	TObjectPtr<UTexture2D> SmallImage = nullptr;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	TObjectPtr<UTexture2D> LargeImage = nullptr;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	EINV_ItemRarity Rarity = EINV_ItemRarity::Common;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	int32 CurrencyValue = 0;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	TObjectPtr<UINV_CategoryViewModel> Category = nullptr;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	int32 RequiredLevel = 0;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	int32 Quantity = 0;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	int32 MaxQuantity = 0;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	bool bIsConsumable = false;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	bool bIsEquippable = false;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	bool bIsDroppable = false;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, Setter)
	bool bIsEquipped = false;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	EINV_ItemEquipType EquipType { EINV_ItemEquipType::None };
	
private:
	void SetMaxQuantity(int32 Value);
	void SetQuantity(int32 Value);
	FINV_ItemIdentification ItemIdentification = {};
};
