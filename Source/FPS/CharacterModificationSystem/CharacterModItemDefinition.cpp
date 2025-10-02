// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterModItemDefinition.h"

#include "CharacterModItemInstance.h"


UItemInstance* UCharacterModItemDefinition::CreateItemInstance_Implementation(UObject* Outer) const
{
	UCharacterModItemInstance* Instance = NewObject<UCharacterModItemInstance>(Outer);
	Instance->Definition = const_cast<UCharacterModItemDefinition*>(this);
	Instance->Quantity = 1;
	Instance->CurrentLevel = 1;
	Instance->bIsEquipped = false;
	
	return Instance;
}
