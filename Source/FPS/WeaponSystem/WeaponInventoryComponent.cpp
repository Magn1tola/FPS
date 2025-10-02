// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponInventoryComponent.h"

#include "WeaponInstance.h"
#include "Characters/PlayerCharacter.h"
#include "Data/WeaponDefinition.h"
#include "Enum/EWeaponSlot.h"


UWeaponInventoryComponent::UWeaponInventoryComponent()
{
	// PrimaryComponentTick.bCanEverTick = true;

	EquippedSlot = EWeaponSlot::Knife;
}

EWeaponSlot UWeaponInventoryComponent::AddWeapon(AWeaponInstance* Weapon)
{
	Weapons.Add(Weapon->DefaultData->Slot, Weapon);

	const FAttachmentTransformRules AttachRules(
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepRelative,
		false);
	Weapon->AttachToComponent(PlayerCharacter->GetFirstPersonMesh(), AttachRules, FName("HandGrip_R"));
	Weapon->SetOwner(PlayerCharacter);
	Weapon->GetWeaponMesh()->SetVisibility(false);
	Weapon->GetWeaponMesh()->SetCastShadow(false);
	Weapon->GetWeaponMesh()->SetOnlyOwnerSee(true);
	Weapon->GetWeaponMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;

	return Weapon->DefaultData->Slot;
}

AWeaponInstance* UWeaponInventoryComponent::EquipWeapon(const EWeaponSlot Slot)
{
	if (!Weapons.Contains(Slot)) return nullptr;

	if (EquippedWeapon)
	{
		EquippedWeapon->GetWeaponMesh()->SetVisibility(false);
		EquippedWeapon->UnEquip();
	}

	EquippedSlot = Slot;
	EquippedWeapon = Weapons[Slot];

	PlayerCharacter->GetThirdPersonWeaponMesh()->SetSkeletalMesh(
		EquippedWeapon->GetWeaponMesh()->GetSkeletalMeshAsset());

	EquippedWeapon->GetWeaponMesh()->SetVisibility(true);
	EquippedWeapon->Equip();

	return EquippedWeapon;
}

void UWeaponInventoryComponent::BeginPlay()
{
	PlayerCharacter = CastChecked<APlayerCharacter>(GetOwner());

	for (TSubclassOf WeaponClass : DefaultWeapons)
	{
		AWeaponInstance* Weapon = GetWorld()->SpawnActor<AWeaponInstance>(WeaponClass);
		AddWeapon(Weapon);
	}
}
