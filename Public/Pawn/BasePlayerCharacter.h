// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "PlayerTypes.h"
#include "BasePlayerCharacter.generated.h"



class UCameraComponent;
class USpringArmComponent;
class UAbilityComponent;
class UArmorComponent;
/**
 * 
 */
UCLASS()
class DAZUNREAL5_API ABasePlayerCharacter : public ABasePawn
{
	GENERATED_BODY()

public:
	ABasePlayerCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	FVector getDesiredMovementC();


	UFUNCTION(BlueprintCallable)
	void updateMana(float amt) {
		safeUpdate(currentMana, maxMana, amt);
	}


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
	bool lockCamera = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool isOccupied = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool isUninterruptibleOccupied = false;



	void Attack();
	void RAttack();
	void UnAttack();
	void controlJog();
	void controlSprint();
	void abilityF();
	void abilityE();
	void abilityQ();
	void basicPunch();

	UFUNCTION(BlueprintCallable)
	void enableWeaponCollision(ECollisionEnabled::Type CollisionEnabled);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability")
	UAbilityComponent* abilityComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Armor_body;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Armor_lower;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UArrowComponent* characterFront;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UArrowComponent* characterBack;

	UArrowComponent* characterLeft;
	UArrowComponent* characterRight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBoxComponent* kickBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBoxComponent* punchBox;

	UFUNCTION(BlueprintCallable)
	void kickBoxTrace() const;

	UFUNCTION(BlueprintCallable)
	void punchBoxTrace();

	virtual void takeDamage(
		const FVector& ImpactPoint,
		float physicalDamageValue,
		EPhysicalDamageType physicalDamageType,
		float magicalDamageValue,
		EMagicalDamageType magicalDamageType,
		float damageForce) override;

	void DirectionalHitReact(const FVector& ImpactPoint);




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float EcurrCD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float EMaxCD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float FcurrCD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float FMaxCD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float QcurrCD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float QMaxCD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PAngleUp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PAngleLeft;

protected:
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void Turn(float Value);

	void pForward(float Value);
	void pLeft(float Value);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private: 


	float cdFillRate = 0.5;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayerActionState playerActionState = EPlayerActionState::EP_UNOCCUPIED;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayerMovementState playerMovementState = EPlayerMovementState::EP_WAlKING;

	void directionalBleed(const FVector& ImpactPoint);

	void doLockCamera();

	void toggleCameraPerspective();

	void controlCamera();

	void BackDodge();
	void FrontDodge();
	void LeftDodge();
	void RightDodge();

	UFUNCTION(BlueprintCallable, Category = "stats")
	void updateStats();


	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ThirdPersonCamera;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FirstPersonCamera;


	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	void resetAttack();


};
