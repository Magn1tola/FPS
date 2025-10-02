#pragma once

#include "CoreMinimal.h"
#include "WeaponAttributesData.generated.h"

struct FDefaultWeaponStats;

USTRUCT(BlueprintType)
struct FWeaponAttributesData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FWeaponAttributesData();
	explicit FWeaponAttributesData(const FDefaultWeaponStats& DefaultStats);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxEnergy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Energy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxDeflection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireCost;
};
