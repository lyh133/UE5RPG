// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Sound/SoundCue.h"
#include "DamageTypes.h"
#include "ArmorComponent.generated.h"
class ABasePlayerCharacter;

UENUM(BlueprintType)
enum class ArmorType : uint8
{
	EA_UpperBody,
	EA_LowerBody,
};

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAZUNREAL5_API UArmorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UArmorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	ABasePlayerCharacter* owner;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite)
	ArmorType armorType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* onHitSound;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* Appearance100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* Appearance75;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* Appearance50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* Appearance25;


	USkeletalMeshComponent* playerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxDurability = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float currDurability = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float bonusPD = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float bonusMD = 0.f;

	UFUNCTION(BlueprintCallable)
	void onAttach();

	UFUNCTION(BlueprintCallable)
	void onDettach();
	void onDamage(float dmg, EPhysicalDamageType dmgType);
private:

};
