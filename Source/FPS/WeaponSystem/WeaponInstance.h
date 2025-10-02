// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameFramework/Actor.h"
#include "WeaponInstance.generated.h"

class UWeaponDefinition;
class UWeaponUpgradeComponent;
struct FWeaponAttributesData;
enum class EWeaponSlot : uint8;
struct FActiveGameplayEffectHandle;
class APlayerCharacter;
struct FGameplayAbilitySpecHandle;
class UGameplayEffect;
class UGameplayAbility;
class UWeaponAttributeSet;
class UFPSAbilitySystemComponent;

UCLASS(BlueprintType)
class FPS_API AWeaponInstance : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Mesh;

public:
	AWeaponInstance();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UWeaponDefinition> DefaultData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int Level;

	UFUNCTION(BlueprintCallable)
	virtual void StartFire();

	UFUNCTION(BlueprintCallable)
	virtual void StopFire();

	UFUNCTION(BlueprintCallable)
	virtual void Equip();

	UFUNCTION(BlueprintCallable)
	virtual void UnEquip();

	UFUNCTION(BlueprintCallable)
	void ChangeShootAbility(TSubclassOf<UGameplayAbility> NewAbility);

	UFUNCTION(BlueprintCallable)
	void ResetShootAbility();

	virtual void SetOwner(AActor* NewOwner) override;

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerCharacter> PlayerCharacter;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UFPSAbilitySystemComponent> PlayerAbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> ShootAbilityClass;

	virtual void BeginPlay() override;

private:
	FGameplayAbilitySpecHandle ShootAbilitySpecHandle;

	bool bIsEquipped;
	bool bIsFiring;
	bool bIsFirstEquip = true;

	float FiringTime;
	float SavedEnergyValue;
	float SavedMaxEnergyValue;
	float SavedEnergyRecoveryValue;

	void ActivateFireAbility() const;
	void SendStopFireGameplayEvent();

public:
	UFUNCTION(BlueprintCallable)
	USkeletalMeshComponent* GetWeaponMesh() const { return Mesh; }

	UFUNCTION(BlueprintCallable)
	APlayerCharacter* GetOwnerPlayer() const { return PlayerCharacter; }
};
