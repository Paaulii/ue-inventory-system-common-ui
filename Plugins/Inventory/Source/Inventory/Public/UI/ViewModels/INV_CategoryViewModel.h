// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "INV_CategoryViewModel.generated.h"

struct FINV_CategoryDisplayData;
struct FINV_ItemDisplayData;
class UINV_ItemViewModel;

UCLASS()
class INVENTORY_API UINV_CategoryViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()
public:
	void Initialize(const FINV_CategoryDisplayData& CategoryData);
	void Deinitialize();
	FText GetCategoryName() const { return CategoryName; }
	TArray<TObjectPtr<UINV_ItemViewModel>> GetCategoryItems() const {return CategoryItems;}
	
protected:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	FText CategoryName;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	TArray<TObjectPtr<UINV_ItemViewModel>> CategoryItems;

private:
	void SetCategoryName(const FText& Name);
	void SetItemArray(const TArray<FINV_ItemDisplayData>&  ItemData);
};
