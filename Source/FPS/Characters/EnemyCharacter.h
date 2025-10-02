// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSCharacterBase.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class FPS_API AEnemyCharacter : public AFPSCharacterBase
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

protected:
	virtual void BeginPlay() override;
};
