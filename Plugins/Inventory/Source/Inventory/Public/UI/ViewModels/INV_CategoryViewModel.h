// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
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
	void SetItems(const TArray<FINV_ItemDisplayData>&  ItemData);

	const FText& GetCategoryName() const { return CategoryName; }
	const TArray<TObjectPtr<UINV_ItemViewModel>>& GetCategoryItems() const { return CategoryItems;}
	const FGameplayTag& GetCategoryTag() const { return Tag;};
protected:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	FText CategoryName;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	TArray<TObjectPtr<UINV_ItemViewModel>> CategoryItems;

private:
	void SetCategoryName(const FText& Name);
	FGameplayTag Tag;
};
