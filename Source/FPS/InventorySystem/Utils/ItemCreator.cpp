// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemCreator.h"

#include "InventorySystem/ItemDefinition.h"


UItemInstance* UItemCreator::CreateItemInstance(UObject* Outer, UItemDefinition* Definition)
{
	return Definition->CreateItemInstance(Outer);
}
