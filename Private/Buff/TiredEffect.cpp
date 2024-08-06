// Fill out your copyright notice in the Description page of Project Settings.


#include "TiredEffect.h"
UTiredEffect::UTiredEffect():UEffectComponent()
{
	
	isTimed = false;
	isTicking = false;
}

void UTiredEffect::onActive()
{
	Super::onActive();

	if (owner)
	{
		owner->currentSprintSpeed = owner->sprintSpeed * strength;
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Green, FString::Printf(TEXT("tiredEFFECT ")));
	}

}

void UTiredEffect::onDeactive(float o)
{
	if (owner)
	{
		owner->currentSprintSpeed = owner->sprintSpeed;
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Green, FString::Printf(TEXT("tiredEFFECT ")));
	}

	Super::onDeactive(1);
}

void UTiredEffect::tickingFunction()
{
	GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Green, FString::Printf(TEXT("tiredEFFECT ")));
}
