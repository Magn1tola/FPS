#pragma once

#include "CoreMinimal.h"
#include "DefaultWeaponStats.generated.h"

USTRUCT(BlueprintType)
struct FPS_API FDefaultWeaponStats
{
	GENERATED_BODY()

public:
	FDefaultWeaponStats(): BaseDamage(0), MaxEnergy(0), MaxDeflection(0), FireRate(0), FireCost(0)
	{
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxEnergy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxDeflection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireCost;
};