// Fill out your copyright notice in the Description page of Project Settings.


#include "ModInstallerComponent.h"

#include "AbilitySystemComponent.h"
#include "CharacterModItemDefinition.h"
#include "CharacterModItemInstance.h"
#include "Characters/FPSCharacterBase.h"


FInstalledModData::FInstalledModData()
{
	ModItem = nullptr;
}

FInstalledModData::FInstalledModData(UCharacterModItemInstance* ModItem, const FActiveGameplayEffectHandle ActiveEffectHandle)
{
	this->ModItem = ModItem;
	this->ActiveEffectHandle = ActiveEffectHandle;
}

UModInstallerComponent::UModInstallerComponent()
{
	Capacity = 10;
	CurrentFullness = 0;
}

bool UModInstallerComponent::CanInstallMod(UCharacterModItemInstance* Mod) const
{
	if (const int Size = Mod->GetDefinition()->Size; Size > Capacity - CurrentFullness)
		return false;

	if (InstalledMods.ContainsByPredicate([Mod](const FInstalledModData& InstalledMod)
	{
		return InstalledMod.ModItem->Definition->GetClass() == Mod->Definition->GetClass();
	}))
		return false;

	return true;
}

void UModInstallerComponent::InstallMod(UCharacterModItemInstance* Mod)
{
	if (!CanInstallMod(Mod)) return;
	
	FInstalledModData ModData;
	ModData.ModItem = Mod;
	ModData.ActiveEffectHandle = ActivateMod(Mod);

	CurrentFullness += Mod->GetDefinition()->Size;
	
	InstalledMods.Add(ModData);
}

void UModInstallerComponent::UninstallMod(const int Id)
{
	if (InstalledMods.Num() - 1 < Id || Id < 0) return;
	const FInstalledModData ModData = InstalledMods[Id];
	OwnerAsc->RemoveActiveGameplayEffect(ModData.ActiveEffectHandle);

	CurrentFullness -= ModData.ModItem->GetDefinition()->Size;

	InstalledMods.RemoveAt(Id);
}

void UModInstallerComponent::ReactivateMods()
{
	CurrentFullness = 0;
	
	for (int i = 0; i < InstalledMods.Num(); i++)
	{
		OwnerAsc->RemoveActiveGameplayEffect(InstalledMods[i].ActiveEffectHandle);
		InstalledMods[i].ActiveEffectHandle = ActivateMod(InstalledMods[i].ModItem);
		CurrentFullness += InstalledMods[i].ModItem->GetDefinition()->Size;
	}
}

void UModInstallerComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<AFPSCharacterBase>(GetOwner());
	OwnerAsc = OwnerCharacter->GetAbilitySystemComponent();
	ReactivateMods();
}

FActiveGameplayEffectHandle UModInstallerComponent::ActivateMod(const UCharacterModItemInstance* Mod) const
{
	const UCharacterModItemDefinition* CharacterModItemDefinition = Cast<UCharacterModItemDefinition>(Mod->Definition);
	const FGameplayEffectContextHandle GameplayEffectContextHandle = OwnerAsc->MakeEffectContext();
	const FGameplayEffectSpecHandle GameplayEffectSpecHandle = OwnerAsc->MakeOutgoingSpec(
		CharacterModItemDefinition->GrantGameplayEffect, Mod->CurrentLevel, GameplayEffectContextHandle);
	return OwnerAsc->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());
}
