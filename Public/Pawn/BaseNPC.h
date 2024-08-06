// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Interface/CombatInterface.h"
#include "Components/WidgetComponent.h"

#include "BaseNPC.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
UCLASS()
class DAZUNREAL5_API ABaseNPC : public ABasePawn 
{
	GENERATED_BODY()


public:


	ABaseNPC();


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBoxComponent* meleeBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "stats")
	float staggerForce;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "stats")
	float knockBackForce;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "stats")
	float meleeRange;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* chargeAnim;


	UFUNCTION(BlueprintCallable, Category = "attack")
	void attack();
	void charge();
	UFUNCTION(BlueprintCallable, Category = "attack")
	void dumbTrace();
	UFUNCTION(BlueprintCallable)
	virtual void takeDamage(
		const FVector& ImpactPoint,
		float physicalDamageValue,
		EPhysicalDamageType physicalDamageType,
		float magicalDamageValue,
		EMagicalDamageType magicalDamageType,
		float damageForce) override;

	void DirectionalHitReact(const FVector& ImpactPoint, const float damageForce);

};
