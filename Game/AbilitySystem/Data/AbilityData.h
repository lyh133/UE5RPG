// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "dazAda/dazAda.h"
#include "GameplayEffect.h"
#include "MarkDefinition.h"
#include "AbilityData.generated.h"


class UAcGameplayAbility;
class UAbilityFragment;
class AAcBaseProjectile;
class UParticleSystem;
class UNiagaraSystem;
class USoundBase;
/**
 * 
 */


UCLASS(Blueprintable)
class DAZADA_API UAbilityData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Display")
	FText AbilityName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Display")
	TObjectPtr<UTexture2D> AbilityIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	TSubclassOf<UAcGameplayAbility> AbilityClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	EAbilityType AbilityType;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EDamageType DamageType;

	// Melee Fields////////////////////////////////////////////////////////////////////////////////////
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability",
	meta = (EditCondition = "AbilityType == EAbilityType::Melee", EditConditionHides))
	bool bHasMeleeForce = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability",
	meta = (EditCondition = "AbilityType == EAbilityType::Melee", EditConditionHides))
	TSubclassOf<UGameplayEffect> MeleeImpactGameplayEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability",
	meta = (EditCondition = "AbilityType == EAbilityType::Melee", EditConditionHides))
	bool bIsMeleeTrace= true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability",
	meta = (EditCondition = "AbilityType == EAbilityType::Melee", EditConditionHides))
	bool bIsMeleeAOE= true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio",
	meta = (EditCondition = "AbilityType == EAbilityType::Melee", EditConditionHides))
	TObjectPtr<USoundBase> MeleeOnHitSound;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX",
	meta = (EditCondition = "AbilityType == EAbilityType::Melee", EditConditionHides))
	TObjectPtr<UParticleSystem> MeleeHitEffect_Cascade;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX",
	meta = (EditCondition = "AbilityType == EAbilityType::Melee", EditConditionHides))
	TObjectPtr<UNiagaraSystem> MeleeHitEffect_Niagara;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX",
	meta = (EditCondition = "AbilityType == EAbilityType::Melee", EditConditionHides))
	TObjectPtr<UParticleSystem> MeleeHitEffect_Cascade_Secondary;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX",
	meta = (EditCondition = "AbilityType == EAbilityType::Melee", EditConditionHides))
	TObjectPtr<UNiagaraSystem> MeleeHitEffect_Niagara_Secondary;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX",
	meta = (EditCondition = "AbilityType == EAbilityType::Melee", EditConditionHides))
	FVector MeleeVFXOffset1 = FVector(0.f, 0.f, 0.f);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX",
	meta = (EditCondition = "AbilityType == EAbilityType::Melee", EditConditionHides))
	FVector MeleeVFXOffset2 = FVector(0.f, 0.f, 0.f);
	///////////////////////////////////////////////////////////////////////////////////




	////Ranged Fields//////////////////////////////////////////////////////////////////////
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability",
		meta = (EditCondition = "AbilityType == EAbilityType::Ranged", EditConditionHides))
	FVector SpawnProjectileOffset = FVector(0.f, 0.f, 0.f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability",
		meta = (EditCondition = "AbilityType == EAbilityType::Ranged", EditConditionHides))
	ERangedAttackType RangedAttackType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability",
		meta = (EditCondition = "AbilityType == EAbilityType::Ranged", EditConditionHides))
	TSubclassOf<AAcBaseProjectile> ProjectileClass;


	///////////////////////////////////////////////////////////////////////////////////
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	float Cooldown = 1.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	float AbilityManaCost = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	float AbilityStaminaCost = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	float AbilityHealthCost = 1.0f;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float BasePhysicalDamage;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float BaseMagicalDamage;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float BaseTrueDamage;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float BaseStaminaDamage;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float BaseManaDamage;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float BaseStanceDamage;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float BaseForce;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float ForceMult;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float AD_Mult;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float AP_Mult;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool ShowOnHUD = true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	TArray<UAbilityFragment*> Fragments;



	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	bool bIsSequenced = false;

	// Highest combo step reachable (e.g. 3 = light-light-light chains up to a 3rd hit)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sequence",
	meta = (EditCondition = "bIsSequenced", EditConditionHides, ClampMin = "1"))
	int32 MaxSequenceCount = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sequence",
	meta = (EditCondition = "bIsSequenced", EditConditionHides, ClampMin = "1"))
	float ComboDuration = 3.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sequence",
	meta = (EditCondition = "bIsSequenced", EditConditionHides))
	TArray<FAbilitySequenceSection> SequenceSections;


	// Marks this ability applies on hit (e.g. an ability that marks for later detonation)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mark")
	TArray<FMarkDefinition> MarksToApply;

	// Marks this ability detonates on hit, if present on the target (e.g. an auto-attack that pops any mark)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mark")
	TArray<FMarkDefinition> MarksToDetonate;
};
