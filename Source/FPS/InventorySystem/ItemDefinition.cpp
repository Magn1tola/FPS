// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemDefinition.h"

#include "InventorySystem/ItemInstance.h"

FPrimaryAssetId UItemDefinition::GetPrimaryAssetId() const
{
	return FPrimaryAssetId("ItemDefinition", GetFName());
}

UItemInstance* UItemDefinition::CreateItemInstance_Implementation(UObject* Outer) const
{
	UItemInstance* Instance = NewObject<UItemInstance>(Outer);
	Instance->Definition = const_cast<UItemDefinition*>(this);
	Instance->Quantity = 1;

	return Instance;
}
