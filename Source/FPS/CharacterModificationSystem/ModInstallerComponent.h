// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "Components/ActorComponent.h"
#include "ModInstallerComponent.generated.h"


class AFPSCharacterBase;
class UCharacterModItemInstance;

USTRUCT(BlueprintType)
struct FInstalledModData
{
	GENERATED_BODY();

public:
	FInstalledModData();
	FInstalledModData(UCharacterModItemInstance* ModItem, FActiveGameplayEffectHandle ActiveEffectHandle);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCharacterModItemInstance> ModItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FActiveGameplayEffectHandle ActiveEffectHandle;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPS_API UModInstallerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UModInstallerComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Capacity;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	int CurrentFullness;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FInstalledModData> InstalledMods;

	UFUNCTION(BlueprintCallable)
	bool CanInstallMod(UCharacterModItemInstance* Mod) const;

	UFUNCTION(BlueprintCallable)
	void InstallMod(UCharacterModItemInstance* Mod);

	UFUNCTION(BlueprintCallable)
	void UninstallMod(int Id);

	UFUNCTION(BlueprintCallable)
	void ReactivateMods();
	
	virtual void BeginPlay() override;

private:
	TObjectPtr<AFPSCharacterBase> OwnerCharacter;
	TObjectPtr<UAbilitySystemComponent> OwnerAsc;

	FActiveGameplayEffectHandle ActivateMod(const UCharacterModItemInstance* Mod) const;
};
