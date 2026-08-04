// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityFragment.h"
#include "AbilityFragmentAnimation.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class DAZADA_API UAbilityFragmentAnimation : public UAbilityFragment
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UAnimMontage> MontageToPlay = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	bool bPlayOnAbilityActivate = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	bool bEndAbilityOnMontageEnd = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	FName TriggerOnNotifyName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	bool bUpperBodyAnim = false;
};
