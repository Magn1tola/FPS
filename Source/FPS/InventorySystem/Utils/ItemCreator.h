// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ItemCreator.generated.h"

class UItemDefinition;
class UItemInstance;

/**
 * Class for easy create ItemInstance from blueprints
 */
UCLASS()
class FPS_API UItemCreator : public UObject
{
	GENERATED_BODY()

public:

	/**
	 * Create ItemInstance from item definition
	 * @param Outer Any object from world (self)
	 * @param Definition
	 */
	UFUNCTION(BlueprintCallable)
	static UItemInstance* CreateItemInstance(UObject* Outer, UItemDefinition* Definition);
};
