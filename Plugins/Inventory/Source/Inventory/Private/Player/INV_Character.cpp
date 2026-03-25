// Copyright Paulina Hałatek, All Rights Reserved.


#include "Player/INV_Character.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AttributeSets/INV_PlayerAttributes.h"


AINV_Character::AINV_Character()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UINV_PlayerAttributes>(TEXT("AttributeSet"));
}

void AINV_Character::BeginPlay()
{
	Super::BeginPlay();
	
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &AINV_Character::NotifyHealthChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHealthAttribute()).AddUObject(this, &AINV_Character::NotifyMaxHealthChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetManaAttribute()).AddUObject(this, &AINV_Character::NotifyManaChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxManaAttribute()).AddUObject(this, &AINV_Character::NotifyMaxManaChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetBaseAttackAttribute()).AddUObject(this, &AINV_Character::NotifyBaseAttackChanged);
	}
	
	ApplyEffects(StartupEffects);
}

UAbilitySystemComponent* AINV_Character::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AINV_Character::ApplyEffects(TArray<TSubclassOf<UGameplayEffect>> EffectsToApply) const
{
	if (AbilitySystemComponent == nullptr )
	{
		return;
	}
	
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	
	for (auto GameplayEffect : EffectsToApply)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
		if (NewHandle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
			// AbilitySystemComponent->RemoveActiveGameplayEffectBySourceEffect(GameplayEffect, nullptr);
		}
	}
}

void AINV_Character::NotifyHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void AINV_Character::NotifyMaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void AINV_Character::NotifyMaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}

void AINV_Character::NotifyBaseAttackChanged(const FOnAttributeChangeData& Data) const
{
	UE_LOG(LogTemp, Warning, TEXT("BASE ATTACK: %f"), Data.NewValue)
	OnBaseAttackChanged.Broadcast(Data.NewValue);
}

void AINV_Character::NotifyManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

