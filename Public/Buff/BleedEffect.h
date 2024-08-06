// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EffectComponent.h"
#include "BleedEffect.generated.h"

/**
 * 
 */
UCLASS()
class DAZUNREAL5_API UBleedEffect : public UEffectComponent
{
	GENERATED_BODY()

public:
	UBleedEffect();
	void onActive() override;
	void onDeactive(float o) override;
	void tickingFunction() override;
private:
	float BleedBurstDMG = 10;
	float BleedDOTDMG = 10;
};
