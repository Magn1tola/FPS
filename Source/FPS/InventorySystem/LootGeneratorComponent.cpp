// Fill out your copyright notice in the Description page of Project Settings.


#include "LootGeneratorComponent.h"

#include "DroppedItem.h"
#include "ItemDefinition.h"
#include "ItemInstance.h"


ULootGeneratorComponent::ULootGeneratorComponent(): bGenerateOnBeginPlay(true), bDropOnce(true)
{
}


void ULootGeneratorComponent::GenerateLoot()
{
	LootItems.Empty();
	for (const FLootGenerationParameters Parameter : LootGenerationParameters)
	{
		if (FMath::FRand() > Parameter.GenerateChance) continue;

		UItemInstance* ItemInstance = Parameter.ItemDefinition->CreateItemInstance(this);
		ItemInstance->Quantity = FMath::RandRange(Parameter.MinQuantity, Parameter.MaxQuantity);

		LootItems.Push(ItemInstance);
	}
}

void ULootGeneratorComponent::Drop()
{
	if (bIsDropped && bDropOnce) return;
	for (UItemInstance* Item : LootItems)
	{
		FVector Location = GetOwner()->GetActorLocation() + SpawnOffset;
		FRotator Rotation = FRotator(0);
		ADroppedItem* DroppedItem = GetWorld()->SpawnActor<ADroppedItem>(SpawnItemClass, Location, Rotation);
		DroppedItem->ItemInstance = Item;
		const FVector2D Circle = FMath::RandPointInCircle(0.5f);
		DroppedItem->GetMesh()->AddImpulse(FVector(Circle.X, Circle.Y,1) * 3500.0f);
	}
}

void ULootGeneratorComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bGenerateOnBeginPlay) GenerateLoot();	
}

