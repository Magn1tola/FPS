// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPlayerState.h"

#include "AbilitySystem/FPSAbilitySystemComponent.h"
#include "AbilitySystem/AttributeSets/BodyEnergyAttributeSet.h"
#include "AbilitySystem/AttributeSets/HealthAttributeSet.h"
#include "AbilitySystem/AttributeSets/WeaponAttributeSet.h"

AFPSPlayerState::AFPSPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UFPSAbilitySystemComponent>(TEXT("Ability System"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	HealthAttributes = CreateDefaultSubobject<UHealthAttributeSet>(TEXT("Health Attributes"));

	BodyEnergyAttributes = CreateDefaultSubobject<UBodyEnergyAttributeSet>(TEXT("Body Energy Attributes"));

	WeaponAttributes = CreateDefaultSubobject<UWeaponAttributeSet>(TEXT("Weapon Attributes"));
}

UAbilitySystemComponent* AFPSPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
