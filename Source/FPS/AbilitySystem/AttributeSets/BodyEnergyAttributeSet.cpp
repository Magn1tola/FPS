// Fill out your copyright notice in the Description page of Project Settings.


#include "BodyEnergyAttributeSet.h"

#include "GameplayEffectExtension.h"

UBodyEnergyAttributeSet::UBodyEnergyAttributeSet()
{
}

void UBodyEnergyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetBodyEnergyAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxBodyEnergy());
	}
	
	Super::PreAttributeChange(Attribute, NewValue);
}

void UBodyEnergyAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetBodyEnergyAttribute())
	{
		SetBodyEnergy(FMath::Clamp(GetBodyEnergy(), 0, GetMaxBodyEnergy()));
	}
}
