// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "AbilitySystem/FPSAbilitySystemComponent.h"
#include "AbilitySystem/AttributeSets/HealthAttributeSet.h"


AEnemyCharacter::AEnemyCharacter()
{
	// PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UFPSAbilitySystemComponent>(TEXT("Ability System Component"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	HealthAttributes = CreateDefaultSubobject<UHealthAttributeSet>(TEXT("Health Attributes"));
	
	AbilitySystemComponent->AddAttributeSetSubobject<UHealthAttributeSet>(HealthAttributes);
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	GiveDefaultAbilities();
	InitDefaultAttributes();
}
