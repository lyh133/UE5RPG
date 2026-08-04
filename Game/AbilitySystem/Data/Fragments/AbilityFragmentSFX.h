#pragma once

#include "CoreMinimal.h"
#include "AbilityFragment.h"
#include "Sound/SoundBase.h"
#include "AbilityFragmentSFX.generated.h"

UENUM(BlueprintType)
enum class ESFXSpawnLocation : uint8
{
	AtOwner,
	AtTarget,
	AtHitLocation
};

UENUM(BlueprintType)
enum class ESFXSpawnTime : uint8
{
	OnActivate,
	OnEnd,
	OnHit,
	OnMontageTrigger
};

UCLASS(BlueprintType, EditInlineNew)
class DAZADA_API UAbilityFragment_SFX : public UAbilityFragment
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SFX")
	TObjectPtr<USoundBase> SoundCue = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SFX")
	ESFXSpawnLocation SpawnLocation = ESFXSpawnLocation::AtOwner;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SFX")
	ESFXSpawnTime SpawnTime = ESFXSpawnTime::OnActivate;
};