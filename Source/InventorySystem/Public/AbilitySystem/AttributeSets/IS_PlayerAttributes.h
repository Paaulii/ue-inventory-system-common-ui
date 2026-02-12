// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "IS_PlayerAttributes.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UIS_PlayerAttributes : public UAttributeSet
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UIS_PlayerAttributes, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Mana")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UIS_PlayerAttributes, Mana)

	UPROPERTY(BlueprintReadOnly, Category = "Armor")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UIS_PlayerAttributes, Armor)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData BaseAttack;
	ATTRIBUTE_ACCESSORS(UIS_PlayerAttributes, BaseAttack)
	
	UPROPERTY(BlueprintReadOnly, Category = "Strength")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UIS_PlayerAttributes, Strength)

	UPROPERTY(BlueprintReadOnly, Category = "Gold")
	FGameplayAttributeData Gold;
	ATTRIBUTE_ACCESSORS(UIS_PlayerAttributes, Gold)
};
