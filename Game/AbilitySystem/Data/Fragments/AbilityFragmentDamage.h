// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "dazAda/dazAda.h"
#include "AbilityFragment.h"
#include "AbilityFragmentDamage.generated.h"



/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class DAZADA_API UAbilityFragmentDamage : public UAbilityFragment
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float DamageAmount = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	EDamageType DamageType = EDamageType::Physical;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	bool bCanCrit = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage", meta = (EditCondition = "bCanCrit", EditConditionHides))
	float CritMultiplier = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	bool bIsOverTime = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage", meta = (EditCondition = "bIsOverTime", EditConditionHides))
	float TickInterval = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage", meta = (EditCondition = "bIsOverTime", EditConditionHides))
	float Duration = 5.0f;
};
