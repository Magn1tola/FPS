// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "FPSAttributeSetBase.h"
#include "BodyEnergyAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UBodyEnergyAttributeSet : public UFPSAttributeSetBase
{
	GENERATED_BODY()

public:
	UBodyEnergyAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	UPROPERTY(BlueprintReadOnly, Category="Ability | Gameplay Attribute")
	FGameplayAttributeData MaxBodyEnergy;

	UPROPERTY(BlueprintReadOnly, Category="Ability | Gameplay Attribute")
	FGameplayAttributeData BodyEnergy;

	UPROPERTY(BlueprintReadOnly, Category="Ability | Gameplay Attribute")
	FGameplayAttributeData BodyEnergyRecovery;
	
	ATTRIBUTE_ACCESSORS(UBodyEnergyAttributeSet, MaxBodyEnergy);
	ATTRIBUTE_ACCESSORS(UBodyEnergyAttributeSet, BodyEnergy);
	ATTRIBUTE_ACCESSORS(UBodyEnergyAttributeSet, BodyEnergyRecovery);
};
