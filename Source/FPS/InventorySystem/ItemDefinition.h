// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDefinition.generated.h"

class UItemInstance;
/**
 * 
 */
UCLASS(BlueprintType)
class FPS_API UItemDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Description;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UItemInstance* CreateItemInstance(UObject* Outer) const;
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

protected:
	virtual UItemInstance* CreateItemInstance_Implementation(UObject* Outer) const;
};
