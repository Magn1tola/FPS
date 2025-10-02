// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"

#include "Interactable.h"


UInteractionComponent::UInteractionComponent()
{
}

void UInteractionComponent::InvokeInteractions(const APlayerCharacter* Player)
{
	for (AActor* Actor : Interactions)
	{
		if (Actor->Implements<UInteractable>())
		{
			IInteractable::Execute_Interact(Actor, Player);
		}
	}
}

