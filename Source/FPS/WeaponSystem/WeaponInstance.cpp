// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponInstance.h"

#include "AbilitySystem/FPSAbilitySystemComponent.h"
#include "AbilitySystem/AttributeSets/WeaponAttributeSet.h"
#include "Characters/PlayerCharacter.h"
#include "Data/WeaponAttributesData.h"
#include "Data/WeaponDefinition.h"


AWeaponInstance::AWeaponInstance()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetTickGroup(TG_PostPhysics);

	Level = 1;
}

void AWeaponInstance::StartFire()
{
	if (!bIsEquipped || bIsFiring) return;
	bIsFiring = true;
	ActivateFireAbility();
}

void AWeaponInstance::StopFire()
{
	if (!bIsEquipped || !bIsFiring) return;
	bIsFiring = false;
	SendStopFireGameplayEvent();
}

void AWeaponInstance::Equip()
{
	if (!PlayerAbilitySystemComponent || bIsEquipped) return;

	ShootAbilitySpecHandle = PlayerAbilitySystemComponent->GiveAbility(ShootAbilityClass);

	FWeaponAttributesData CurrentAttributes = FWeaponAttributesData(DefaultData->Stats);
	CurrentAttributes.Damage = DefaultData->GetDamageByLevel(Level);
	CurrentAttributes.Energy = bIsFirstEquip ? CurrentAttributes.MaxEnergy : SavedEnergyValue;
	PlayerCharacter->GetWeaponAttributes()->InitFromData(CurrentAttributes);

	bIsEquipped = true;
	bIsFirstEquip = false;
}

void AWeaponInstance::UnEquip()
{
	if (!PlayerAbilitySystemComponent || !bIsEquipped) return;

	PlayerAbilitySystemComponent->CancelAbilityHandle(ShootAbilitySpecHandle);
	PlayerAbilitySystemComponent->SetRemoveAbilityOnEnd(ShootAbilitySpecHandle);

	bIsEquipped = false;
	SavedEnergyValue = PlayerCharacter->GetWeaponAttributes()->GetEnergy();
	SavedMaxEnergyValue = PlayerCharacter->GetWeaponAttributes()->GetMaxEnergy();
	SavedEnergyRecoveryValue = PlayerCharacter->GetWeaponAttributes()->GetEnergyRecovery();
}

void AWeaponInstance::ChangeShootAbility(const TSubclassOf<UGameplayAbility> NewAbility)
{
	ShootAbilityClass = NewAbility;
	
	if (bIsEquipped)
	{
		PlayerAbilitySystemComponent->CancelAbilityHandle(ShootAbilitySpecHandle);
		PlayerAbilitySystemComponent->SetRemoveAbilityOnEnd(ShootAbilitySpecHandle);

		ShootAbilitySpecHandle = PlayerAbilitySystemComponent->GiveAbility(ShootAbilityClass);
	}
}

void AWeaponInstance::ResetShootAbility()
{
	ChangeShootAbility(DefaultData->ShootGameplayAbility);
}

void AWeaponInstance::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);

	PlayerCharacter = Cast<APlayerCharacter>(NewOwner);
	if (PlayerCharacter)
		PlayerAbilitySystemComponent = Cast<UFPSAbilitySystemComponent>(PlayerCharacter->GetAbilitySystemComponent());
}

void AWeaponInstance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!PlayerCharacter) return;
	if (bIsFiring)
	{
		FiringTime += DeltaTime;
	}

	if (!bIsEquipped && SavedEnergyValue != SavedMaxEnergyValue)
	{
		SavedEnergyValue += FMath::Lerp(0, SavedEnergyRecoveryValue * 10, DeltaTime);
		SavedEnergyValue = FMath::Clamp(SavedEnergyValue, 0, SavedMaxEnergyValue);
	}
}

void AWeaponInstance::BeginPlay()
{
	Super::BeginPlay();
	if (DefaultData)
	{
		SavedEnergyValue = DefaultData->Stats.MaxEnergy;
		ShootAbilityClass = DefaultData->ShootGameplayAbility;
	}
}

void AWeaponInstance::ActivateFireAbility() const
{
	if (!PlayerAbilitySystemComponent) return;
	PlayerAbilitySystemComponent->TryActivateAbility(ShootAbilitySpecHandle);
}

void AWeaponInstance::SendStopFireGameplayEvent()
{
	if (!PlayerAbilitySystemComponent) return;
	FGameplayEventData Data;
	Data.EventTag = FGameplayTag::RequestGameplayTag("Gameplay.Weapon.Event.StopFire");
	Data.Instigator = PlayerCharacter;
	Data.EventMagnitude = FiringTime;

	PlayerAbilitySystemComponent->HandleGameplayEvent(Data.EventTag, &Data);

	FiringTime = 0;
}
