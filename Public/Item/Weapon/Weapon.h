// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "DamageTypes.h"
#include "Sound/SoundCue.h"
#include "Weapon.generated.h"

/**
 * 
 */
class UBoxComponent;
class UNiagaraSystem;
class UNiagaraComponent;

struct WeaponBuffParam
{
	float duration;
	float baseMagicInc;
	float basePhysicalInc;
};


UCLASS()
class  AWeapon : public AActor
{
	GENERATED_BODY()

public:
	AWeapon();


	UPROPERTY(VisibleAnywhere, Category = "Weapon VFX")
	UNiagaraComponent* weaponVFX;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Trace VFX")
	//UNiagaraComponent* TraceVFX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Anim")
	UAnimMontage* basicAnim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Anim")
	UAnimMontage* RightBasicAnim;

	UFUNCTION(BlueprintCallable)
	UAnimMontage* getBasicAnim();

	UFUNCTION(BlueprintCallable)
	UAnimMontage* getRightBasicAnim();
	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon Property")
	UStaticMeshComponent* weaponMesh;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* onSwingSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundCue* onHitSound;

	//damage = weaponBaseAD + player AD * weapon multiplier

	float totalPhysicalDMG();
	float totalMagicalDMG();
	float totalForce();

	float getOwnerAD();
	float getOwnerAP();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Stats")
	float weaponBaseForce;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Stats")
	float weaponBaseAD;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Stats")
	float weaponBaseAP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Stats")
	float weaponForceMultiplier;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Stats")
	float weaponADMultipler;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Stats")
	float weaponAPMultipler;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Stats")
	float attackCD;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Stats")
	float staminaCost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Stats")
	int maxSeq = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Stats")
	int RmaxSeq = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Stats")
	EPhysicalDamageType weaponPhysicalDamageType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon Stats")
	EMagicalDamageType weaponMagicalDamageType;



	void activeWeaponBuff(WeaponBuffParam param);
	void deactiveWeaponBuff(WeaponBuffParam param);

protected:
	USceneComponent* rootComponent;

	



private:

	

	



};
