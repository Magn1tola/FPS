// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorsMagnetComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPS_API UActorsMagnetComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UActorsMagnetComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> AttractingClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bCanAttractActors = true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float ItemsAttractionDistance = 500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float AttractionSpeed = 100.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float OverlapItemsFrequency = 0.3f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TArray<AActor*> OverlappingActors;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	float CurrentTimer = 0;

	void SphereOverlap();

	void AttractActors();
};
