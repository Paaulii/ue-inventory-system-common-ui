// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "StructUtils/InstancedStruct.h"
#include "INV_CategoryViewModel.generated.h"

struct FINV_ItemDefinitionData;
struct FINV_CategoryData;
class UINV_ItemViewModel;
/**
 * 
 */
UCLASS()
class INVENTORY_API UINV_CategoryViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()
public:
	void Initialize(const FINV_CategoryData& CategoryData);
	void Deinitialize();
	FText GetCategoryName() const { return CategoryName; }
	UTexture2D* GetCategoryIcon() const { return CategoryIcon; }
	TArray<TObjectPtr<UINV_ItemViewModel>> GetCategoryItems() const {return CategoryItems;}
	
protected:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	FText CategoryName;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	UTexture2D* CategoryIcon;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	TArray<TObjectPtr<UINV_ItemViewModel>> CategoryItems;

private:
	void SetCategoryName(const FText& Name);
	void SetCategoryIcon(UTexture2D* Icon);
	void SetItemArray(const TArray<TInstancedStruct<FINV_ItemDefinitionData>>& ItemData);
};
