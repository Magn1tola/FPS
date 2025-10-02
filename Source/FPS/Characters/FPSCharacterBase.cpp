// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacterBase.h"

#include "AbilitySystem/FPSAbilitySystemComponent.h"


AFPSCharacterBase::AFPSCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

UAbilitySystemComponent* AFPSCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UHealthAttributeSet* AFPSCharacterBase::GetHealthAttributes() const
{
	return HealthAttributes;
}

void AFPSCharacterBase::GiveDefaultAbilities()
{
	check(AbilitySystemComponent);
	if (!HasAuthority()) return;

	for (const TSubclassOf AbilityClass : DefaultAbilities)
	{
		const FGameplayAbilitySpec AbilitySpec(AbilityClass, 1);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}

void AFPSCharacterBase::InitDefaultAttributes() const
{
	if (!AbilitySystemComponent) return;

	for (const TSubclassOf AttributeEffect : DefaultGameplayEffects)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(
			AttributeEffect, 1.0f, EffectContext);

		if (!SpecHandle.IsValid()) continue;
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}
