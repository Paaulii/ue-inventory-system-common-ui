#include "AbilitySystem/AttributeSets/INV_PlayerAttributes.h"

void UINV_PlayerAttributes::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		Health = FMath::Clamp<float>(NewValue, 0.0f, GetMaxHealth());
	}
	else if (Attribute == GetManaAttribute())
	{
		Mana = FMath::Clamp<float>(NewValue, 0.0f, GetMaxMana());
	}
}