// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "INV_Character.generated.h"

class UINV_PlayerAttributes;
class UGameplayEffect;
struct FOnAttributeChangeData;

DECLARE_MULTICAST_DELEGATE_OneParam(FPlayerStatChange, int32);

UCLASS()
class INVENTORY_API AINV_Character : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AINV_Character();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	void ApplyEffects(TArray<TSubclassOf<UGameplayEffect>> EffectsToApply) const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	FPlayerStatChange OnHealthChanged;
	FPlayerStatChange OnMaxHealthChanged;
	FPlayerStatChange OnManaChanged;
	FPlayerStatChange OnMaxManaChanged;
protected:
	virtual void BeginPlay() override;
	void NotifyHealthChanged(const FOnAttributeChangeData& Data) const;
	void NotifyMaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void NotifyManaChanged(const FOnAttributeChangeData& Data) const;
	void NotifyMaxManaChanged(const FOnAttributeChangeData& Data) const;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayEffect>> StartupEffects;

	UPROPERTY()
	TObjectPtr<UINV_PlayerAttributes> AttributeSet;
};
