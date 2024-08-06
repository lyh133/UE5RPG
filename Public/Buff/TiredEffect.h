// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectComponent.h"
#include "TiredEffect.generated.h"

/**
 * 
 */
UCLASS()
class DAZUNREAL5_API UTiredEffect : public UEffectComponent
{
	GENERATED_BODY()

public:
	UTiredEffect();

	void onActive() override;
	void onDeactive(float o) override;
	void tickingFunction() override;
};
