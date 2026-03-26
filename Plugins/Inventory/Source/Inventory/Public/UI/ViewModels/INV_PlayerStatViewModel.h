// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/MVVM/UIS_ViewModelBase.h"
#include "INV_PlayerStatViewModel.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UINV_PlayerStatViewModel : public UUIS_ViewModelBase
{
	GENERATED_BODY()
public:
	virtual void Initialize() override;

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetHealthPercent() const;
	
	UFUNCTION(BlueprintPure, FieldNotify)
	float GetManaPercent() const;

	float GetStatPercent(int32 CurrentValue, int32 MaxValue) const;
	int32 GetCurrentHealth() const { return CurrentHealth; }
	int32 GetMaxHealth() const { return MaxHealth; }
	int32 GetCurrentMana() const { return CurrentMana; }
	int32 GetMaxMana() const { return MaxMana; }
	int32 GetArmor() const { return Armor; }
	int32 GetBaseAttack() const { return BaseAttack; }
	int32 GetMagicPower() const { return MagicPower; }

	void SetCurrentHealth(int32 Value);
	void SetMaxHealth(int32 Value);
	void SetCurrentMana(int32 Value);
	void SetMaxMana(int32 Value);
	void SetArmor(int32 Value);
	void SetBaseAttack(int32 Value);
	void SetMagicPower(int32 Value);
protected:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter)
	int32 CurrentHealth = 0;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter)
	int32 MaxHealth = 0;
	
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter)
	int32 CurrentMana = 0;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter)
	int32 MaxMana = 0;
	
	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter)
	int32 Armor = 0;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter)
	int32 BaseAttack = 0;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Getter)
	int32 MagicPower = 0;
};
