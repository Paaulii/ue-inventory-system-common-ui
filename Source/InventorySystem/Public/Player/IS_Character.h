// Copyright Paulina Hałatek, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "IS_Character.generated.h"

struct FOnAttributeChangeData;
class UIS_PlayerAttributes;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_MULTICAST_DELEGATE_OneParam(FPlayerStatChange, int32);

UCLASS()
class INVENTORYSYSTEM_API AIS_Character : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	AIS_Character();
 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	FPlayerStatChange OnHealthChanged;	
	FPlayerStatChange OnMaxHealthChanged;	
	FPlayerStatChange OnManaChanged;	
	FPlayerStatChange OnMaxManaChanged;	
	
protected:
	virtual void BeginPlay() override;
	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void AddStartupEffects();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
	void NotifyHealthChanged(const FOnAttributeChangeData& Data) const;
	void NotifyMaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void NotifyManaChanged(const FOnAttributeChangeData& Data) const;
	void NotifyMaxManaChanged(const FOnAttributeChangeData& Data) const;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	
	UPROPERTY()
	TObjectPtr<UIS_PlayerAttributes> AttributeSet;
};
