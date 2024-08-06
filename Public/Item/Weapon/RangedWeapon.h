// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "item/MeleeWeapon.h"
#include "RangedWeapon.generated.h"
/**
 * 
 */
class UArrowComponent;
class ABaseProjectile;
UCLASS()
class DAZUNREAL5_API ARangedWeapon : public AMeleeWeapon
{
	GENERATED_BODY()
public:
	ARangedWeapon();

	UPROPERTY(VisibleAnywhere, Category = "Weapon Property")
	UArrowComponent* firePoint;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Property")
	TSubclassOf<ABaseProjectile> projectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Property")
	TSubclassOf<ABaseProjectile> chargedProjectileClass;

	
	UFUNCTION(BlueprintCallable)
	void fire();

	UFUNCTION(BlueprintCallable)
	void Tracefire();

	UFUNCTION(BlueprintCallable)
	void fireChargedShot();

private:
	void InitProjectileStats(ABaseProjectile* projectile);
};
