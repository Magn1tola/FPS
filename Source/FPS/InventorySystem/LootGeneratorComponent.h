// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LootGeneratorComponent.generated.h"

class ADroppedItem;
class UItemInstance;
class UItemDefinition;

USTRUCT(BlueprintType)
struct FLootGenerationParameters
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UItemDefinition> ItemDefinition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MinQuantity = 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MaxQuantity = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float GenerateChance;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPS_API ULootGeneratorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	ULootGeneratorComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<ADroppedItem> SpawnItemClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FLootGenerationParameters> LootGenerationParameters;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bGenerateOnBeginPlay;

	UPROPERTY(EditDefaultsOnly)
	bool bDropOnce;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector SpawnOffset;
	
	UFUNCTION(BlueprintCallable)
	void GenerateLoot();

	UFUNCTION(BlueprintCallable)
	void Drop();
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleInstanceOnly)
	TArray<TObjectPtr<UItemInstance>> LootItems;

	bool bIsDropped = false;
};
