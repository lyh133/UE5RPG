#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "dazAda/dazAda.h"
#include "ProjectileDataAsset.generated.h"

class UParticleSystem;
class UNiagaraSystem;
class USoundBase;

UCLASS(Blueprintable, BlueprintType)
class DAZADA_API UProjectileDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	// ===== VFX =====

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="VFX")
	TObjectPtr<UParticleSystem> Base_Cascade;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="VFX")
	TObjectPtr<UNiagaraSystem> Base_Niagara;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="VFX")
	TObjectPtr<UParticleSystem> HitEffect_Cascade;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="VFX")
	TObjectPtr<UNiagaraSystem> HitEffect_Niagara;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="VFX")
	TObjectPtr<UParticleSystem> HitEffect_Cascade_Secondary;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="VFX")
	TObjectPtr<UNiagaraSystem> HitEffect_Niagara_Secondary;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="VFX")
	FVector SpawnVFXOffset1 = FVector(0.f, 0.f, 0.f);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="VFX")
	FVector SpawnVFXOffset2 = FVector(0.f, 0.f, 0.f);
	// ===== SFX =====
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Audio")
	TObjectPtr<USoundBase> HitSound;

	// ===== Lifetime =====
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Projectile")
	float LifeSpan = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Projectile")
	float SphereRadius = 32.f;		

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Projectile")
	float InitProjectileSpeed = 2000.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Projectile")
	float FinalProjectileSpeed = 2000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Movement")
	bool bRotationFollowsVelocity = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Movement")
	float GravityScale = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Projectile")
	bool bISAOE = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Projectile")
	bool bHasForce = true;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EDamageType DamageType;
};