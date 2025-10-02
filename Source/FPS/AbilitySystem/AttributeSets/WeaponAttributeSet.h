// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "FPSAttributeSetBase.h"
#include "WeaponAttributeSet.generated.h"

struct FWeaponAttributesData;

/**
 * 
 */
UCLASS()
class FPS_API UWeaponAttributeSet : public UFPSAttributeSetBase
{
	GENERATED_BODY()

public:
	UWeaponAttributeSet();


	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	UPROPERTY(BlueprintReadOnly, Category= "Ability | Gameplay Attribute")
	FGameplayAttributeData Damage;

	UPROPERTY(BlueprintReadOnly, Category= "Ability | Gameplay Attribute")
	FGameplayAttributeData MaxEnergy;

	UPROPERTY(BlueprintReadOnly, Category= "Ability | Gameplay Attribute")
	FGameplayAttributeData Energy;

	UPROPERTY(BlueprintReadOnly, Category= "Ability | Gameplay Attribute")
	FGameplayAttributeData EnergyRecovery;
	
	/**
	 * Maximum deviation of the projectile from the aiming line, when firing at 100 meters.
	 * The value is specified in cm.
	 */
	UPROPERTY(BlueprintReadOnly, Category= "Ability | Gameplay Attribute")
	FGameplayAttributeData MaxDeflection;

	/**
	 * Delay in seconds between shoots.
	 */
	UPROPERTY(BlueprintReadOnly, Category= "Ability | Gameplay Attribute")
	FGameplayAttributeData FireRate;

	UPROPERTY(BlueprintReadOnly, Category= "Ability | Gameplay Attribute")
	FGameplayAttributeData FireCost;

	ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, Damage);
	ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, MaxEnergy);
	ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, Energy);
	ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, EnergyRecovery);
	ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, MaxDeflection);
	ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, FireRate);
	ATTRIBUTE_ACCESSORS(UWeaponAttributeSet, FireCost);
	
	void InitFromData(const FWeaponAttributesData& Data);
	void Clear();
};
