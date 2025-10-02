// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


class UItemDefinition;
class UItemInstance;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<UItemInstance>> Inventory;

	UFUNCTION(BlueprintCallable)
	void AddItem(UItemInstance* NewItem);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool HasItem(const UItemDefinition* Definition) const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UItemInstance* GetItemByDefinition(const UItemDefinition* Definition);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<UItemInstance*> GetItemsByClass(TSubclassOf<UItemDefinition> Class) const;
};
