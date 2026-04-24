#include "Player/INV_Character.h"
#include "AbilitySystem/AttributeSets/INV_PlayerAttributes.h"
#include "AbilitySystemComponent.h"

AINV_Character::AINV_Character()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(FName("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UINV_PlayerAttributes>(FName("AttributeSet"));
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
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetArmorAttribute()).AddUObject(this, &AINV_Character::NotifyArmorChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMagicPowerAttribute()).AddUObject(this, &AINV_Character::NotifyMagicPowerChanged);
	}
	
	ApplyEffects(StartupEffects);
}

void AINV_Character::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).RemoveAll(this);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHealthAttribute()).RemoveAll(this);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetManaAttribute()).RemoveAll(this);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxManaAttribute()).RemoveAll(this);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetBaseAttackAttribute()).RemoveAll(this);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetArmorAttribute()).RemoveAll(this);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMagicPowerAttribute()).RemoveAll(this);
	}
}

UAbilitySystemComponent* AINV_Character::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AINV_Character::ApplyEffects(const TArray<TSubclassOf<UGameplayEffect>>& EffectsToApply) const
{
	if (AbilitySystemComponent == nullptr )
	{
		return;
	}
	
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	
	for (const auto& GameplayEffect : EffectsToApply)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
		if (NewHandle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
		}
	}
}

void AINV_Character::RevokeEffects(const TArray<TSubclassOf<UGameplayEffect>>& EffectsToRevoke) const
{
	if (AbilitySystemComponent == nullptr )
	{
		return;
	}

	for (const auto& GameplayEffect : EffectsToRevoke)
	{
		AbilitySystemComponent->RemoveActiveGameplayEffectBySourceEffect(GameplayEffect, AbilitySystemComponent);
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

void AINV_Character::NotifyManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void AINV_Character::NotifyMaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}

void AINV_Character::NotifyBaseAttackChanged(const FOnAttributeChangeData& Data) const
{
	OnBaseAttackChanged.Broadcast(Data.NewValue);
}

void AINV_Character::NotifyArmorChanged(const FOnAttributeChangeData& Data) const
{
	OnArmorChanged.Broadcast(Data.NewValue);
}

void AINV_Character::NotifyMagicPowerChanged(const FOnAttributeChangeData& Data) const
{
	OnMagicPowerChanged.Broadcast(Data.NewValue);
}
