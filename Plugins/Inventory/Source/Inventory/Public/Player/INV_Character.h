#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "INV_Character.generated.h"

class UGameplayEffect;
class UINV_PlayerAttributes;
struct FOnAttributeChangeData;

UCLASS()
class INVENTORY_API AINV_Character : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AINV_Character();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	void ApplyEffects(const TArray<TSubclassOf<UGameplayEffect>>& EffectsToApply) const;
	void RevokeEffects(const TArray<TSubclassOf<UGameplayEffect>>& EffectsToRevoke) const;

	DECLARE_MULTICAST_DELEGATE_OneParam(FINV_PlayerStatChange, int32);
	FINV_PlayerStatChange OnHealthChanged;
	FINV_PlayerStatChange OnMaxHealthChanged;
	FINV_PlayerStatChange OnManaChanged;
	FINV_PlayerStatChange OnMaxManaChanged;
	FINV_PlayerStatChange OnBaseAttackChanged;
	FINV_PlayerStatChange OnArmorChanged;
	FINV_PlayerStatChange OnMagicPowerChanged;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayEffect>> StartupEffects = {};

private:
	void NotifyHealthChanged(const FOnAttributeChangeData& Data) const;
	void NotifyMaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void NotifyManaChanged(const FOnAttributeChangeData& Data) const;
	void NotifyMaxManaChanged(const FOnAttributeChangeData& Data) const;
	void NotifyBaseAttackChanged(const FOnAttributeChangeData& Data) const;
	void NotifyArmorChanged(const FOnAttributeChangeData& Data) const;
	void NotifyMagicPowerChanged(const FOnAttributeChangeData& Data) const;
	
	UPROPERTY()
	TObjectPtr<UINV_PlayerAttributes> AttributeSet = nullptr;
};
