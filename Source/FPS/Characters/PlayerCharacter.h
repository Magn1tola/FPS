// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FPSCharacterBase.h"
#include "Logging/LogMacros.h"
#include "PlayerCharacter.generated.h"

class UActorsMagnetComponent;
class UModInstallerComponent;
class UInventoryComponent;
class UInteractorComponent;
class UBodyEnergyAttributeSet;
class UWeaponInventoryComponent;
class UWeaponAttributeSet;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;

struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A basic first person character
 */
UCLASS(abstract)
class APlayerCharacter : public AFPSCharacterBase
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> FirstPersonMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> ThirdPersonWeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FirstPersonCameraComponent;

	UPROPERTY(VIsibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UModInstallerComponent> ModInstallerComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UActorsMagnetComponent> MagnetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWeaponInventoryComponent> WeaponInventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInteractorComponent> InteractorComponent;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input")
	UInputAction* MouseLookAction;

public:
	APlayerCharacter();

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UBodyEnergyAttributeSet> BodyEnergyAttributes;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UWeaponAttributeSet> WeaponAttributes;

	void MoveInput(const FInputActionValue& Value);

	void LookInput(const FInputActionValue& Value);

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

public:
	
	UFUNCTION(BlueprintCallable)
	USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }

	UFUNCTION(BlueprintCallable)
	USkeletalMeshComponent* GetThirdPersonWeaponMesh() const { return ThirdPersonWeaponMesh; }

	UFUNCTION(BlueprintCallable)
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UFUNCTION(BlueprintCallable)
	UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

	UFUNCTION(BlueprintCallable)
	UWeaponInventoryComponent* GetWeaponInventoryComponent() const { return WeaponInventoryComponent; }

	UFUNCTION(BlueprintCallable)
	UInteractorComponent* GetInteractorComponent() const { return InteractorComponent; }

	UFUNCTION(BlueprintCallable)
	UWeaponAttributeSet* GetWeaponAttributes() const { return WeaponAttributes; }

	UFUNCTION(BlueprintCallable)
	UBodyEnergyAttributeSet* GetBodyEnergyAttributes() const { return BodyEnergyAttributes; }

private:
	void InitAbilitySystemComponent();
};
