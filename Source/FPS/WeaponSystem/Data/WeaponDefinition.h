// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefaultWeaponStats.h"
#include "Engine/DataAsset.h"
#include "WeaponDefinition.generated.h"

enum class EWeaponSlot : uint8;
class UGameplayAbility;

/**
 * 
 */
UCLASS(BlueprintType)
class FPS_API UWeaponDefinition : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDefaultWeaponStats Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageScaleByLevel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayAbility> ShootGameplayAbility;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponSlot Slot;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetDamageByLevel(const int Level) const;
};
