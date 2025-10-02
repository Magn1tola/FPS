// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponDefinition.h"

float UWeaponDefinition::GetDamageByLevel(const int Level) const
{
	return Stats.BaseDamage * (DamageScaleByLevel * (Level - 1) + 1);
}
