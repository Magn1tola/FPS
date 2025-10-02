// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "FPSAttributeSetBase.h"
#include "HealthAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API UHealthAttributeSet : public UFPSAttributeSetBase
{
	GENERATED_BODY()

public:
	UHealthAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxHealth, Category="Ability | Gameplay Attribute")
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Health, Category="Ability | Gameplay Attribute")
	FGameplayAttributeData Health;

	UPROPERTY()
	FGameplayAttributeData MetaHealing;

	UPROPERTY()
	FGameplayAttributeData MetaDamage;

	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, MetaHealing);
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, MetaDamage);

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
};
