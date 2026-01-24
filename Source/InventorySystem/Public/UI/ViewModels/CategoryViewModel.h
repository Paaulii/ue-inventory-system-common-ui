// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "StructUtils/InstancedStruct.h"
#include "CategoryViewModel.generated.h"

struct FItemData;
struct FCategoryData;
class UItemViewModel;
/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UCategoryViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()
public:
	void Initialize(const FCategoryData& CategoryData);
	void Deinitialize();
	FText GetCategoryName() const { return CategoryName; }
	UTexture2D* GetCategoryIcon() const { return CategoryIcon; }
	TArray<TObjectPtr<UItemViewModel>> GetCategoryItems() const {return CategoryItems;}
	
protected:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	FText CategoryName;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	UTexture2D* CategoryIcon;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	TArray<TObjectPtr<UItemViewModel>> CategoryItems;

private:
	void SetCategoryName(const FText& Name);
	void SetCategoryIcon(UTexture2D* Icon);
	void SetItemArray(const TArray<TInstancedStruct<FItemData>>& ItemData);
};
