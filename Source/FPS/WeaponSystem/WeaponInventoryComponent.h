// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponInventoryComponent.generated.h"


class APlayerCharacter;
class AWeaponInstance;
enum class EWeaponSlot : uint8;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPS_API UWeaponInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeaponInventoryComponent();

	UFUNCTION(BlueprintCallable)
	EWeaponSlot AddWeapon(AWeaponInstance* Weapon);

	UFUNCTION(BlueprintCallable)
	AWeaponInstance* EquipWeapon(EWeaponSlot Slot);

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerCharacter> PlayerCharacter;
	
	UPROPERTY(BlueprintReadOnly)
	TMap<EWeaponSlot, TObjectPtr<AWeaponInstance>> Weapons;

	UFUNCTION(BlueprintCallable)
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AWeaponInstance>> DefaultWeapons;
	
	TObjectPtr<AWeaponInstance> EquippedWeapon;
	
	EWeaponSlot EquippedSlot;

public:
	UFUNCTION(BlueprintCallable)
	AWeaponInstance* GetEquippedWeapon() const { return EquippedWeapon; }

	UFUNCTION(BlueprintCallable)
	EWeaponSlot GetEquippedSlot() const { return EquippedSlot; }
};
