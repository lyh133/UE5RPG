// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityComponent.generated.h"

class ABasePawn;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DAZUNREAL5_API UAbilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* animDodge;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* animKick;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* animDashAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* animWaveAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* animChargedShot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* animDoubleShot;

	void dodge();
	void kick();
	void chargedShot();


	void dashAttack();
	void fireyBlade();

private:
	ABasePawn* ownerCharacter;


		
};
