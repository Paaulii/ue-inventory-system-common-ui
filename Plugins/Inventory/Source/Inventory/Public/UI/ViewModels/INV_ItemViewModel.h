// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "INV_CategoryViewModel.h"
#include "MVVMViewModelBase.h"
#include "Data/Types/INV_ItemRarity.h"
#include "INV_ItemViewModel.generated.h"

UCLASS()
class INVENTORY_API UINV_ItemViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()
public:
	void Initialize(const FINV_ItemDisplayData& ItemData, UINV_CategoryViewModel* CategoryVM);
	FText GetItemName() const { return ItemName; }
	FText GetDescription() const { return Description; }
	UTexture2D* GetSmallImage() const { return SmallImage; }
	UTexture2D* GetLargeImage() const { return LargeImage; }
	EINV_ItemRarity GetRarity() const { return Rarity; }
	int32 GetCurrencyValue() const { return CurrencyValue; }
	bool GetIsEquipped() const { return IsEquipped; }
	UINV_CategoryViewModel* GetCategory() const { return Category; }
	int32 GetRequiredLevel() const { return RequiredLevel; }
	int32 GetQuantity() const { return Quantity; }
	bool GetEquippable() const { return Equippable;}
	bool GetConsumable() const { return Consumable;}
	bool GetDroppable() const { return Droppable;}
protected:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	FText ItemName;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	FText Description;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	UTexture2D* SmallImage;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	UTexture2D* LargeImage;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	EINV_ItemRarity Rarity;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	int32 CurrencyValue;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	bool IsEquipped;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, Setter)
	TObjectPtr<UINV_CategoryViewModel> Category;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	int32 RequiredLevel;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	int32 Quantity;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	bool Consumable;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	bool Equippable;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	bool Droppable;
private:
	void SetItemName(const FText& Name);
	void SetDescription(const FText& NewDescription);
	void SetSmallImage(UTexture2D* Image);
	void SetLargeImage(UTexture2D* Image);
	void SetRarity(const EINV_ItemRarity& ItemRarity);
	void SetCurrencyValue(const int32 Currency);
	void SetCategory(UINV_CategoryViewModel* CategoryVM);
	void SetIsEquipped(bool bState);
	void SetRequiredLevel(int32 Level);
	void SetQuantity(int32 Value);
	void SetConsumable(bool bState);
	void SetEquippable(bool bState);
	void SetDroppable(bool bState);
};
