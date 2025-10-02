// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractorComponent.h"

#include "InteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "Characters/PlayerCharacter.h"


UInteractorComponent::UInteractorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UInteractorComponent::InteractWithTarget() const
{
	if (TargetInteractionComponent)
	{
		TargetInteractionComponent->InvokeInteractions(PlayerCharacter);
	}
}


void UInteractorComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = CastChecked<APlayerCharacter>(GetOwner());
}


void UInteractorComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	const FVector Start = PlayerCharacter->GetFirstPersonCameraComponent()->GetComponentLocation();
	const FVector ForwardVector = PlayerCharacter->GetFirstPersonCameraComponent()->GetForwardVector();
	const FVector End = Start + ForwardVector * 500.0f;

	FCollisionQueryParams Cqp;
	Cqp.AddIgnoredActor(PlayerCharacter);
	if (FHitResult Hit; GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Cqp))
	{
		const AActor* Actor = Hit.Component->GetOwner();
		
		if (UInteractionComponent* Component = Actor->GetComponentByClass<UInteractionComponent>())
		{
			TargetInteractionComponent = Component;
		}
	}

}

