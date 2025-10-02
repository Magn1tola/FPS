// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DroppedItem.generated.h"

class UItemInstance;

UCLASS()
class FPS_API ADroppedItem : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

public:
	ADroppedItem();

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	TObjectPtr<UItemInstance> ItemInstance;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
	UStaticMeshComponent* GetMesh() { return Mesh; }
};
