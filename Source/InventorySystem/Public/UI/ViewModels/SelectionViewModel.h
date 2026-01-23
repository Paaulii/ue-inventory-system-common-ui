// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ItemViewModel.h"
#include "MVVMViewModelBase.h"
#include "SelectionViewModel.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API USelectionViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()
public:
	UCategoryViewModel* GetSelectedCategory() const { return SelectedCategory; }
	UItemViewModel* GetSelectedItem() const { return SelectedItem; }
protected:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	UCategoryViewModel* SelectedCategory;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Getter)
	UItemViewModel* SelectedItem;
};
