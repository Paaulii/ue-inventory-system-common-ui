// Copyright Paulina Hałatek, All Rights Reserved.


#include "UI/ViewModels/IS_PlayerStatViewModel.h"

#include "Player/IS_Character.h"
#include "Player/UIS_PlayerController.h"

void UIS_PlayerStatViewModel::Initialize()
{
	Super::Initialize();
	if (AUIS_PlayerController* PlayerController = Cast<AUIS_PlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		if (AIS_Character* Character = Cast<AIS_Character>(PlayerController->GetCharacter()))
		{
			Character->OnHealthChanged.AddWeakLambda(this, [this](int32 Value)
			{
				SetCurrentHealth(Value);
			});

			Character->OnMaxHealthChanged.AddWeakLambda(this, [this](int32 Value)
			{
				SetMaxHealth(Value);
			});

			Character->OnManaChanged.AddWeakLambda(this, [this](int32 Value)
			{
				SetCurrentMana(Value);
			});

			Character->OnMaxManaChanged.AddWeakLambda(this, [this](int32 Value)
			{
				SetMaxMana(Value);
			});
		}
	}
}

float UIS_PlayerStatViewModel::GetHealthPercent() const
{
	return GetStatPercent(CurrentHealth, MaxHealth);
}

float UIS_PlayerStatViewModel::GetManaPercent() const
{
	return GetStatPercent(CurrentMana, MaxMana);
}

float UIS_PlayerStatViewModel::GetStatPercent(int32 CurrentValue, int32 MaxValue) const
{
	if (MaxValue != 0)
	{
		return static_cast<float>(CurrentValue / MaxValue);
	}

	return 0;
}

void UIS_PlayerStatViewModel::SetCurrentHealth(int32 Value)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(CurrentHealth, Value))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);
	}
}

void UIS_PlayerStatViewModel::SetMaxHealth(int32 Value)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(MaxHealth, Value))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);
	}
}

void UIS_PlayerStatViewModel::SetCurrentMana(int32 Value)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(CurrentMana, Value))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetManaPercent);
	}
}

void UIS_PlayerStatViewModel::SetMaxMana(int32 Value)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(MaxMana, Value))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetManaPercent);
	}
}