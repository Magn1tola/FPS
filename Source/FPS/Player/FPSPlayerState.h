// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "FPSPlayerState.generated.h"

class UBodyEnergyAttributeSet;
class UWeaponAttributeSet;
class UHealthAttributeSet;
class UFPSAttributeSetBase;
class UFPSAbilitySystemComponent;

UCLASS()
class FPS_API AFPSPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AFPSPlayerState();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFPSAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UHealthAttributeSet> HealthAttributes;

	UPROPERTY()
	TObjectPtr<UBodyEnergyAttributeSet> BodyEnergyAttributes; 
	
	UPROPERTY()
	TObjectPtr<UWeaponAttributeSet> WeaponAttributes;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UHealthAttributeSet* GetPlayerAttributes() const { return HealthAttributes; }
	virtual UBodyEnergyAttributeSet* GetBodyEnergyAttributes() const { return BodyEnergyAttributes; }
	virtual UWeaponAttributeSet* GetWeaponAttributes() const { return WeaponAttributes; }
};
