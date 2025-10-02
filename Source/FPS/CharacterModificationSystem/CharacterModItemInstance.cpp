// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterModItemInstance.h"

#include "CharacterModItemDefinition.h"

UCharacterModItemDefinition* UCharacterModItemInstance::GetDefinition() const
{
	return Cast<UCharacterModItemDefinition>(Definition);
}
