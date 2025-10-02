// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "WeaponSystem/Data/WeaponAttributesData.h"

UWeaponAttributeSet::UWeaponAttributeSet()
{
}

void UWeaponAttributeSet::InitFromData(const FWeaponAttributesData& Data)
{
	SetDamage(Data.Damage);
	SetMaxEnergy(Data.MaxEnergy);
	SetEnergy(Data.Energy);
	SetMaxDeflection(Data.MaxDeflection);
	SetFireRate(Data.FireRate);
	SetFireCost(Data.FireCost);
	SetEnergyRecovery(3);
}

void UWeaponAttributeSet::Clear()
{
	SetDamage(0);
	SetMaxEnergy(0);
	SetEnergy(0);
	SetMaxDeflection(0);
	SetFireRate(0);
	SetFireCost(0);
	SetEnergyRecovery(3);
}

void UWeaponAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetEnergyAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxEnergy());
	}
	
	Super::PreAttributeChange(Attribute, NewValue);
}

void UWeaponAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetEnergyAttribute())
	{
		SetEnergy(FMath::Clamp(GetEnergy(), 0, GetMaxEnergy()));
	}
}
