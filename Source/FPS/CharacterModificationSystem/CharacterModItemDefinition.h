// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventorySystem/ItemDefinition.h"
#include "CharacterModItemDefinition.generated.h"

class UGameplayEffect;
/**
 * 
 */
UCLASS()
class FPS_API UCharacterModItemDefinition : public UItemDefinition
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> GrantGameplayEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Size;
	
protected:
	virtual UItemInstance* CreateItemInstance_Implementation(UObject* Outer) const override;
};
