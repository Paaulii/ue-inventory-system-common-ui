// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/ViewModels/ItemViewModel.h"

#include "Data/ItemData.h"

void UItemViewModel::Initialize(const FItemData* ItemData, UCategoryViewModel* CategoryVM)
{
	SetItemName(ItemData->Name);
	SetDescription(ItemData->Description);
	SetSmallImage(ItemData->SmallImage);
	SetLargeImage(ItemData->LargeImage);
	SetRarity(ItemData->Rarity);
	SetCurrencyValue(ItemData->CurrencyValue);
	SetIsEquipped(false);
	SetCategory(CategoryVM);
	SetRequiredLevel(ItemData->RequiredLevel);
}

void UItemViewModel::SetItemName(const FText& Name)
{
	UE_MVVM_SET_PROPERTY_VALUE(ItemName, Name);
}

void UItemViewModel::SetDescription(const FText& NewDescription)
{
	UE_MVVM_SET_PROPERTY_VALUE(Description, NewDescription);
}

void UItemViewModel::SetSmallImage(UTexture2D* Image)
{
	UE_MVVM_SET_PROPERTY_VALUE(SmallImage, Image);
}

void UItemViewModel::SetLargeImage(UTexture2D* Image)
{
	UE_MVVM_SET_PROPERTY_VALUE(LargeImage, Image);
}

void UItemViewModel::SetRarity(const EItemRarity& ItemRarity)
{
	UE_MVVM_SET_PROPERTY_VALUE(Rarity, ItemRarity);
}

void UItemViewModel::SetCurrencyValue(const int32 Currency)
{
	UE_MVVM_SET_PROPERTY_VALUE(CurrencyValue, Currency);
}

void UItemViewModel::SetIsEquipped(bool bState)
{
	UE_MVVM_SET_PROPERTY_VALUE(IsEquipped, bState);
}

void UItemViewModel::SetIsEmpty(bool bState)
{
	UE_MVVM_SET_PROPERTY_VALUE(IsEmpty, bState);
}

void UItemViewModel::SetCategory(UCategoryViewModel* CategoryVM)
{
	UE_MVVM_SET_PROPERTY_VALUE(Category, CategoryVM);
}

void UItemViewModel::SetRequiredLevel(int32 Level)
{
	UE_MVVM_SET_PROPERTY_VALUE(RequiredLevel, Level);
}
