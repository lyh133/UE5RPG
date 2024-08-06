// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Weapon.h"
#include "Interface/CombatInterface.h"
#include "Sound/SoundCue.h"

#include "BasePawn.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
UCLASS()
class DAZUNREAL5_API ABasePawn : public ACharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void playHitReactionMontage(const FName& section);

	void safeUpdate(float& attribute, float maxAttribute, float value);
	float resistDamage(float dmg, float resist);
	float timeUntilResetPoise;
public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float maxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float currentHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float maxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float currentStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float maxMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float currentMana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float physicalDefense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float magicalDefense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float currentPoise;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float maxPoise = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float poiseResetTime;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float healthRegen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float staminaRegen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float manaRegen;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float attackSpeed = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float attackCD = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	bool canAttack = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float physicalPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float magicalPower;

	UPROPERTY(BlueprintReadOnly, Category = "Stats")
	bool isAttacking;


	UPROPERTY(BlueprintReadOnly)
	int attackSeq = 1;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float movementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float basicAcceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float jogSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float jogAcceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float sprintSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float currentSprintSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float sprintAcceleration;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	bool isStunned;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	bool isKnockDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	bool isInjured;



	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundWave* onHitSoundLight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundWave* onHitSoundMedium;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundWave* onHitSoundHeavy;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundWave* onAttackSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* onHitBodySound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	AWeapon* equiptWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* onHitLightAnims;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* onHitHeavyAnims;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* onKOAnims;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* baseAttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* backDodgeMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* frontDodgeMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* leftDodgeMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* rightDodgeMontage;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	TArray<UAnimMontage*> punchMontages;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	TArray<UAnimMontage*> kickMontages;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	bool isUpperBody;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* sharpLightOnhitEfect;

public:	


	void playAttackMontage();
	void playRAttackMontage();

	void FunctionToExecuteOnAnimationBlendOut(UAnimMontage* animMontage, bool bInterrupted);
	void FunctionToExecuteOnAnimationEnd(UAnimMontage* animMontage, bool bInterrupted);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttackFinish);
	UPROPERTY(BlueprintAssignable)
	FAttackFinish attackFinish;


	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void setActiveWeapon(AWeapon* weapon) {
		equiptWeapon = weapon;
	}
	UFUNCTION(BlueprintCallable, Category = "stats")
	void changeHP(float amt) {
		safeUpdate(currentHP, maxHP, amt);
	}

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void takeDamage(
		const FVector& ImpactPoint,
		float physicalDamageValue,
		EPhysicalDamageType physicalDamageType,
		float magicalDamageValue,
		EMagicalDamageType magicalDamageType,
		float damageForce) override;

	void onKnockDown();

	FName FindHitDirection(const FVector& ImpactPoint) const;

	//void ApplyBuff(TFunction<void()> buffFunc, TFunction<void()> debuffFunc, float duration);


	void applyStunDuration(float duration);

	void stun()
	{
		isStunned = true;
	};
	void unstun()
	{
		isStunned = false;
	}

};
