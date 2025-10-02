// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "ItemDefinition.h"
#include "ItemInstance.h"


UInventoryComponent::UInventoryComponent()
{
}


void UInventoryComponent::AddItem(UItemInstance* NewItem)
{
	if (!NewItem)
	{
		UE_LOG(LogTemp, Error, TEXT("%hs: New Item not valid"), __FUNCTION__);
		return;
	}
	
	if (HasItem(NewItem->Definition))
	{
		const TObjectPtr<UItemInstance> Item = GetItemByDefinition(NewItem->Definition);
		Item->Quantity += NewItem->Quantity;
	}
	else
	{
		Inventory.Add(NewItem);
	}
}

bool UInventoryComponent::HasItem(const UItemDefinition* Definition) const
{
	return Inventory.ContainsByPredicate([Definition](const UItemInstance* Item)
	{
		return Item->Definition->GetClass() == Definition->GetClass();
	});
}

UItemInstance* UInventoryComponent::GetItemByDefinition(const UItemDefinition* Definition)
{
	return Inventory.FindByPredicate([Definition](const TObjectPtr<UItemInstance>& Item)
	{
		return Item->Definition->GetClass() == Definition->GetClass();
	})->Get();
}

TArray<UItemInstance*> UInventoryComponent::GetItemsByClass(TSubclassOf<UItemDefinition> Class) const
{
	return Inventory.FilterByPredicate([Class](const TObjectPtr<UItemInstance>& Item)
	{
		return Item->Definition->IsA(Class);
	});
}
