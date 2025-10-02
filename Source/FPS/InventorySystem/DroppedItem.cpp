// Fill out your copyright notice in the Description page of Project Settings.


#include "DroppedItem.h"

#include "InventoryComponent.h"
#include "Characters/PlayerCharacter.h"


ADroppedItem::ADroppedItem()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetSimulatePhysics(true);
	Mesh->SetCollisionResponseToAllChannels(ECR_Block);
	Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = Mesh;
}

void ADroppedItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (const TCopyQualifiersFromTo_T<AActor, APlayerCharacter>* Player = Cast<APlayerCharacter>(OtherActor))
	{
		Player->GetInventoryComponent()->AddItem(ItemInstance);
		Destroy();
	}
}

