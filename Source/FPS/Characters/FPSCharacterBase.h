// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "FPSCharacterBase.generated.h"

class UHealthAttributeSet;
class UGameplayEffect;
class UFPSAttributeSetBase;
class UGameplayAbility;
class UFPSAbilitySystemComponent;

UCLASS()
class FPS_API AFPSCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AFPSCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UHealthAttributeSet* GetHealthAttributes() const;

protected:
	void GiveDefaultAbilities();
	void InitDefaultAttributes() const;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Abilities")
	TObjectPtr<UFPSAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UHealthAttributeSet> HealthAttributes;

	UPROPERTY(EditDefaultsOnly, Category="Ability")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly, Category="Ability")
	TArray<TSubclassOf<UGameplayEffect>> DefaultGameplayEffects;
};
