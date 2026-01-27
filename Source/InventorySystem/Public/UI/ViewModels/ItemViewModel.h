// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CategoryViewModel.h"
#include "Data/ItemRarity.h"
#include "MVVMViewModelBase.h"
#include "ItemViewModel.generated.h"

UCLASS()
class INVENTORYSYSTEM_API UItemViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()
public:
	void Initialize(const FItemData* ItemData, UCategoryViewModel* CategoryVM);
	FText GetItemName() const { return ItemName; }
	FText GetDescription() const { return Description; }
	UTexture2D* GetSmallImage() const { return SmallImage; }
	UTexture2D* GetLargeImage() const { return LargeImage; }
	EItemRarity GetRarity() const { return Rarity; }
	int32 GetCurrencyValue() const { return CurrencyValue; }
	bool GetIsEquipped() const { return IsEquipped; }
	bool GetIsEmpty() const { return IsEmpty; }
	UCategoryViewModel* GetCategory() const { return Category; }
	int32 GetRequiredLevel() const { return RequiredLevel; }
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
	EItemRarity Rarity;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	int32 CurrencyValue;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	bool IsEquipped;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	bool IsEmpty;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter, Setter)
	TObjectPtr<UCategoryViewModel> Category;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	int32 RequiredLevel;
private:
	void SetItemName(const FText& Name);
	void SetDescription(const FText& NewDescription);
	void SetSmallImage(UTexture2D* Image);
	void SetLargeImage(UTexture2D* Image);
	void SetRarity(const EItemRarity& ItemRarity);
	void SetCurrencyValue(const int32 Currency);
	void SetCategory(UCategoryViewModel* CategoryVM);
	void SetIsEquipped(bool bState);
	void SetIsEmpty(bool bState);
	void SetRequiredLevel(int32 Level);
};
