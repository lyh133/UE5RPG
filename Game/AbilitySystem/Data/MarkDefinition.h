#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MarkDefinition.generated.h"

class UGameplayEffect;
class USoundBase;
class UNiagaraSystem;

USTRUCT(BlueprintType)
struct FMarkDefinition
{
	GENERATED_BODY()

	// Identifies this mark type — must match the tag granted by ApplyEffect
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mark")
	FGameplayTag MarkTag;

	// GE that grants the mark. Duration, stacking, max stacks, and refresh-on-reapply
	// are all configured on this GE asset itself (Stacking = Aggregate By Target,
	// Stack Limit Count = N, Duration Refresh Policy = Refresh On Successful Application).
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mark")
	TSubclassOf<UGameplayEffect> ApplyEffect;

	// GE that fires when this mark detonates.
	// If bDetonateDealsDamage is true, this must read Data.PhysicalDamage/Data.ArPen/etc.
	// SetByCaller tags (same shape as the main DamageGameplayEffect) — damage is computed
	// from source stats and applied through ApplyDamage.
	// If false, this is applied directly (status effects like slow/stun, no damage math).
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mark")
	TSubclassOf<UGameplayEffect> DetonateEffect;

	// Must match ApplyEffect's Stack Limit Count. Detonation only fires once this many stacks are present.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mark", meta = (ClampMin = "1"))
	int32 MaxStacks = 1;

	// ===========================
	// Detonation damage (only used if bDetonateDealsDamage is true)
	// ===========================
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mark|Damage")
	bool bDetonateDealsDamage = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mark|Damage", meta = (EditCondition = "bDetonateDealsDamage", EditConditionHides))
	float DetonateBaseDamage = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mark|Damage", meta = (EditCondition = "bDetonateDealsDamage", EditConditionHides))
	float DetonateADMult = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mark|Damage", meta = (EditCondition = "bDetonateDealsDamage", EditConditionHides))
	float DetonateAPMult = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mark|Damage", meta = (EditCondition = "bDetonateDealsDamage", EditConditionHides))
	EDamageType DetonateDamageType = EDamageType::Physical;

	// ===========================
	// One-shot cosmetics
	// ===========================
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mark|VFX")
	USoundBase* ApplySFX = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mark|VFX")
	UNiagaraSystem* ApplyVFX = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mark|VFX")
	USoundBase* DetonateSFX = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mark|VFX")
	UNiagaraSystem* DetonateVFX = nullptr;

	// ===========================
	// Persistent while-marked VFX
	// ===========================
	// GameplayCue tag driving the looping/attached VFX while the mark is active.
	// Add this same tag to ApplyEffect's Gameplay Cues list; a GameplayCueNotify_Actor
	// bound to this tag handles spawn/attach on OnActive and cleanup on OnRemove automatically.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mark|VFX")
	FGameplayTag PersistentVFXCueTag;
};