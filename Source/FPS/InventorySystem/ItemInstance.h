// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemInstance.generated.h"

class UItemDefinition;

UCLASS(BlueprintType)
class UItemInstance : public UObject
{
	GENERATED_BODY()

public:
	UItemInstance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UItemDefinition> Definition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Quantity;
};
