// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorsMagnetComponent.h"

#include "Engine/OverlapResult.h"


// Sets default values for this component's properties
UActorsMagnetComponent::UActorsMagnetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UActorsMagnetComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                 FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurrentTimer += DeltaTime;
	if (CurrentTimer > OverlapItemsFrequency)
	{
		CurrentTimer = 0.0f;
		SphereOverlap();
	}
	AttractActors();
}

void UActorsMagnetComponent::SphereOverlap()
{
	OverlappingActors.Empty();

	TArray<FOverlapResult> OverlapResults;
	const FVector Location = GetOwner()->GetActorLocation();
	const FQuat Rotation = FQuat::Identity;
	const FCollisionShape Sphere = FCollisionShape::MakeSphere(ItemsAttractionDistance);
	GetWorld()->OverlapMultiByChannel(OverlapResults, Location, Rotation, ECC_WorldDynamic, Sphere);

	if (OverlapResults.IsEmpty()) return;

	for (FOverlapResult& Result : OverlapResults)
	{
		if (Result.GetActor()->IsA(AttractingClass))
		{
			OverlappingActors.Add(Result.GetActor());
		}
	}
}

void UActorsMagnetComponent::AttractActors()
{
	if (!bCanAttractActors) return;

	for (AActor* Actor : OverlappingActors)
	{
		FVector From = Actor->GetActorLocation();
		FVector To = GetOwner()->GetActorLocation();
		FVector Direction = To - From;
		const float Speed = FMath::Clamp(AttractionSpeed, 0.0f, Direction.Length());
		Direction.Normalize();
		FVector NewLocation = From + Direction * Speed;
		Actor->SetActorLocation(NewLocation);
	}
}
