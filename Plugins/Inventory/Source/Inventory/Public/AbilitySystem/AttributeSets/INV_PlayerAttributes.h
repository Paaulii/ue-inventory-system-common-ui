// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "INV_PlayerAttributes.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class INVENTORY_API UINV_PlayerAttributes : public UAttributeSet
{
	GENERATED_BODY()
public:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UINV_PlayerAttributes, Health)
	
	UPROPERTY(BlueprintReadOnly, Category = "MaxHealth")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UINV_PlayerAttributes, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Mana")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UINV_PlayerAttributes, Mana)
	
	UPROPERTY(BlueprintReadOnly, Category = "MaxMana")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UINV_PlayerAttributes, MaxMana)

	UPROPERTY(BlueprintReadOnly, Category = "Armor")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UINV_PlayerAttributes, Armor)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData BaseAttack;
	ATTRIBUTE_ACCESSORS(UINV_PlayerAttributes, BaseAttack)
	
	UPROPERTY(BlueprintReadOnly, Category = "Strength")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UINV_PlayerAttributes, Strength)

	UPROPERTY(BlueprintReadOnly, Category = "Gold")
	FGameplayAttributeData Gold;
	ATTRIBUTE_ACCESSORS(UINV_PlayerAttributes, Gold)
};
