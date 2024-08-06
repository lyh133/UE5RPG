// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectComponent.h"
#include "BasePawn.h"
// Sets default values for this component's properties
UEffectComponent::UEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	owner = Cast<ABasePawn>(GetOwner());

	// ...
}


// Called when the game starts
void UEffectComponent::BeginPlay()
{
	Super::BeginPlay();


	
}

void UEffectComponent::onActive()
{
	RegisterComponent();
	if (isTicking)
	{
		FTimerHandle tickingHandle;
		GetWorld()->GetTimerManager().SetTimer(tickingHandle, this, &UEffectComponent::tickingFunction, tickInterval, true, 0.f);
	}

}

void UEffectComponent::onDeactive(float o)
{
	
}

void UEffectComponent::tickingFunction()
{
}


// Called every frame
void UEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEffectComponent::activeEffect()
{

	onActive();
	if (isTimed)
	{
		FTimerHandle TimerHandle_Delay;
		FTimerDelegate effectDelegate = FTimerDelegate::CreateUObject(this, &UEffectComponent::onDeactive, 0.1f);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_Delay, effectDelegate, duration, false);
		GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Green, FString::Printf(TEXT("timed ")));
	}

}

void UEffectComponent::deactiveEffect()
{
	onDeactive(0.1f);
}

