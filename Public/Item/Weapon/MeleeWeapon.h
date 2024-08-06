// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Interface/CombatInterface.h"
#include "MeleeWeapon.generated.h"

/**
 * 
 */
class UBoxComponent;
class UNiagaraSystem;
class UNiagaraComponent;



UCLASS()
class DAZUNREAL5_API AMeleeWeapon : public AWeapon
{
	GENERATED_BODY()
public:
	AMeleeWeapon();



   //todo create a struct
	//void deactivate

protected:
	UPROPERTY(VisibleAnywhere, Category = "Weapon Property")
	UBoxComponent* weaponBox;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Property")
	USceneComponent* weaponTop;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Property")
	USceneComponent* weaponBot;

	UFUNCTION()
	virtual void OnBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	virtual void BeginPlay() override;

private:
	

public:

	UPROPERTY(VisibleAnywhere, Category = "Weapon Property")
	bool isTraceWeapon = true;

	TArray<AActor*> ignoreActors;
	FORCEINLINE UBoxComponent* GetWeaponBox() const { return weaponBox; }
};
