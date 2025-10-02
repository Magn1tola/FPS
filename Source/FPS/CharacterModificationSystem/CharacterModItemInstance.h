// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventorySystem/ItemInstance.h"
#include "CharacterModItemInstance.generated.h"

class UCharacterModItemDefinition;
/**
 * 
 */
UCLASS()
class FPS_API UCharacterModItemInstance : public UItemInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	int CurrentLevel;

	UPROPERTY(BlueprintReadWrite)
	bool bIsEquipped;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UCharacterModItemDefinition* GetDefinition() const;
};
