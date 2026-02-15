// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/MVVM/UIS_ViewModelBase.h"
#include "IS_PlayerStatViewModel.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYSYSTEM_API UIS_PlayerStatViewModel : public UUIS_ViewModelBase
{
	GENERATED_BODY()
public:
	virtual void Initialize() override;

	UFUNCTION(BlueprintPure, FieldNotify)
	float GetHealthPercent() const;
	
	UFUNCTION(BlueprintPure, FieldNotify)
	float GetManaPercent() const;

	float GetStatPercent(int32 CurrentValue, int32 MaxValue) const;
	
	int32 GetCurrentHealth() const { return CurrentHealth;}
	int32 GetMaxHealth() const { return MaxHealth;}
	
	int32 GetCurrentMana() const { return CurrentMana;}
	int32 GetMaxMana() const { return MaxMana;}

	void SetCurrentHealth(int32 Value);
	void SetMaxHealth(int32 Value);

	void SetCurrentMana(int32 Value);
	void SetMaxMana(int32 Value);
protected:
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	int32 CurrentHealth;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	int32 MaxHealth;
	
	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	int32 CurrentMana;

	UPROPERTY(BlueprintReadWrite, FieldNotify, Setter, Getter)
	int32 MaxMana;
};
