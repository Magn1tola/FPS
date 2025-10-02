// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponAttributesData.h"

#include "DefaultWeaponStats.h"

FWeaponAttributesData::FWeaponAttributesData(): Damage(0), MaxEnergy(0), Energy(0), MaxDeflection(0),
                                                FireRate(0), FireCost(0)
{
}

FWeaponAttributesData::FWeaponAttributesData(const FDefaultWeaponStats& DefaultStats)
{
	Damage = DefaultStats.BaseDamage;
	MaxEnergy = DefaultStats.MaxEnergy;
	Energy = MaxEnergy;
	MaxDeflection = DefaultStats.MaxDeflection;
	FireRate = DefaultStats.FireRate;
	FireCost = DefaultStats.FireCost;
}
