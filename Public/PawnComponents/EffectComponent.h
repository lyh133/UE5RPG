// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EffectComponent.generated.h"

class ABasePawn;



struct {
	int myNum;
} myStructure;




UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAZUNREAL5_API UEffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEffectComponent();

	bool isTimed = true;
	bool isTicking = true;
	float duration = 0.f;
	float strength = 0.f;
	float tickInterval = 1.0f;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void onActive();
	virtual void onDeactive(float o);
	virtual void tickingFunction();

	ABasePawn* owner;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void activeEffect();
	void deactiveEffect();
};
