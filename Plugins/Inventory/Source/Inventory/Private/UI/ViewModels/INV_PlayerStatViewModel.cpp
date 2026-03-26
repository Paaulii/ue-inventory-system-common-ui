// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/ViewModels/INV_PlayerStatViewModel.h"

#include "Player/UIS_PlayerController.h"
#include "Player/INV_Character.h"

void UINV_PlayerStatViewModel::Initialize()
{
	Super::Initialize();
	if (AUIS_PlayerController* PlayerController = Cast<AUIS_PlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		if (AINV_Character* Character = Cast<AINV_Character>(PlayerController->GetCharacter()))
		{
			Character->OnHealthChanged.AddUObject(this, &UINV_PlayerStatViewModel::SetCurrentHealth);
			Character->OnMaxHealthChanged.AddUObject(this, &UINV_PlayerStatViewModel::SetMaxHealth);
			Character->OnManaChanged.AddUObject(this, &UINV_PlayerStatViewModel::SetCurrentMana);
			Character->OnMaxManaChanged.AddUObject(this, &UINV_PlayerStatViewModel::SetMaxMana);
			Character->OnArmorChanged.AddUObject(this, &UINV_PlayerStatViewModel::SetArmor);
			Character->OnBaseAttackChanged.AddUObject(this, &UINV_PlayerStatViewModel::SetBaseAttack);
			Character->OnMagicPowerChanged.AddUObject(this, &UINV_PlayerStatViewModel::SetMagicPower);
		}
	}
}

float UINV_PlayerStatViewModel::GetHealthPercent() const
{
	return GetStatPercent(CurrentHealth, MaxHealth);
}

float UINV_PlayerStatViewModel::GetManaPercent() const
{
	return GetStatPercent(CurrentMana, MaxMana);
}

float UINV_PlayerStatViewModel::GetStatPercent(int32 CurrentValue, int32 MaxValue) const
{
	if (MaxValue != 0)
	{
		return CurrentValue / (static_cast<float>(MaxValue));
	}

	return 0;
}

void UINV_PlayerStatViewModel::SetCurrentHealth(int32 Value)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(CurrentHealth, Value))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);
	}
}

void UINV_PlayerStatViewModel::SetMaxHealth(int32 Value)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(MaxHealth, Value))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);
	}
}

void UINV_PlayerStatViewModel::SetCurrentMana(int32 Value)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(CurrentMana, Value))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetManaPercent);
	}
}

void UINV_PlayerStatViewModel::SetMaxMana(int32 Value)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(MaxMana, Value))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetManaPercent);
	}
}

void UINV_PlayerStatViewModel::SetArmor(int32 Value)
{
	UE_MVVM_SET_PROPERTY_VALUE(Armor, Value);
}

void UINV_PlayerStatViewModel::SetBaseAttack(int32 Value)
{
	UE_MVVM_SET_PROPERTY_VALUE(BaseAttack, Value);
}

void UINV_PlayerStatViewModel::SetMagicPower(int32 Value)
{
	UE_MVVM_SET_PROPERTY_VALUE(MagicPower, Value);
}
