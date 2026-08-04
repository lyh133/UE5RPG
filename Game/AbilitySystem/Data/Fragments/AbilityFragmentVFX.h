// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "AbilityFragment.h"
#include "NiagaraSystem.h"
#include "Particles/ParticleSystem.h"
#include "AbilityFragmentVFX.generated.h"

UENUM(BlueprintType)
enum class ESpawnLocation : uint8
{
	AtOwner,
	AtTarget,
	AtHitLocation
};

UENUM(BlueprintType)
enum class EVFXSpawnTime : uint8
{
	OnActivate,
	OnEnd,
	OnHit,
	OnMontageTrigger
};
UENUM(BlueprintType)
enum class EVFXType : uint8
{
	Cascade,
	Niagara
};

UCLASS(BlueprintType, EditInlineNew)
class DAZADA_API UAbilityFragment_VFX : public UAbilityFragment
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
	TObjectPtr<UNiagaraSystem> ParticleSystem = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
	TObjectPtr<UParticleSystem> CascadeSystem = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
	ESpawnLocation SpawnLocation = ESpawnLocation::AtOwner;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
	FVector Scale = FVector(1.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
	FVector SpawnLocationOffset = FVector(1.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
	EVFXSpawnTime SpawnTime = EVFXSpawnTime::OnActivate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
	bool bAttachToOwner = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="VFX")
	EVFXType VFXType = EVFXType::Niagara;
};