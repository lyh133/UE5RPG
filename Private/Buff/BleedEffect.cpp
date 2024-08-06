// Fill out your copyright notice in the Description page of Project Settings.


#include "BleedEffect.h"
#include "Interface/CombatInterface.h"
#include "DamageTypes.h"
UBleedEffect::UBleedEffect()
{
	isTimed = true;
	isTicking = true;
	
}

void UBleedEffect::onActive()
{
	Super::onActive();

	if (owner)
	{

		if (owner)
		{
			BleedBurstDMG = owner->maxHP * 0.2 * strength;
			BleedDOTDMG = owner->maxHP * 0.02 * strength;
		}
		ICombatInterface* combatInterface = Cast<ICombatInterface>(owner);
		combatInterface->takeDamage(owner->GetActorLocation(), BleedBurstDMG, EPhysicalDamageType::EP_BLEED, 0.f, EMagicalDamageType::EM_DEFAULT, 0.f);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Green, FString::Printf(TEXT("tiredEFFECT ")));
	}
}

void UBleedEffect::onDeactive(float o)
{
	if (owner)
	{

	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Green, FString::Printf(TEXT("tiredEFFECT ")));
	}
	GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Green, FString::Printf(TEXT("deacted ")));
	DestroyComponent();
}

void UBleedEffect::tickingFunction()
{
	ICombatInterface* combatInterface = Cast<ICombatInterface>(owner);
	combatInterface->takeDamage(owner->GetActorLocation(), BleedDOTDMG, EPhysicalDamageType::EP_BLEED, 0.f, EMagicalDamageType::EM_DEFAULT, 0.f);
}

