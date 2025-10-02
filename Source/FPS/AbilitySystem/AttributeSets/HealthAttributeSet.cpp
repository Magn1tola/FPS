// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UHealthAttributeSet::UHealthAttributeSet()
{
}

void UHealthAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UHealthAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UHealthAttributeSet, Health, COND_None, REPNOTIFY_Always);
}

void UHealthAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetMetaDamageAttribute())
	{
		const float DamageValue = GetMetaDamage();
		const float OldHealthValue = GetHealth();
		const float MaxHealthValue = GetMaxHealth();

		if (const float NewHealthValue = FMath::Clamp(OldHealthValue - DamageValue, 0, MaxHealthValue);
			NewHealthValue != OldHealthValue)
		{
			SetHealth(NewHealthValue);
		}

		SetMetaDamage(0.0f);
	}
	else if (Data.EvaluatedData.Attribute == GetMetaHealingAttribute())
	{
		const float HealingValue = GetMetaHealing();
		const float OldHealthValue = GetHealth();
		const float MaxHealthValue = GetMaxHealth();

		if (const float NewHealthValue = FMath::Clamp(OldHealthValue + HealingValue, 0, MaxHealthValue);
			NewHealthValue != OldHealthValue)
		{
			SetHealth(NewHealthValue);
		}

		SetMetaHealing(0.0f);
	}
}

void UHealthAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHealthAttributeSet, MaxHealth, OldMaxHealth);
}

void UHealthAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UHealthAttributeSet, Health, OldHealth);
}
