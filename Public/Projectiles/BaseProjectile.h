// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageTypes.h"
#include "BaseProjectile.generated.h"

class UBoxComponent;
class USphereComponent;
UCLASS()
class DAZUNREAL5_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon Property")
	UStaticMeshComponent* projectileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	float projectileRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	float projectileBaseAD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	float projectileBaseAP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	float projectileADMult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	float projectileAPMult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	float projectileBaseForce;


	float weaponBaseForce;


	float weaponBaseAD;


	float weaponBaseAP;


	EPhysicalDamageType weaponPhysicalDamageType;


	EMagicalDamageType weaponMagicalDamageType;




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Property")
	UBoxComponent* projectileBox;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Property")
	USphereComponent* projectileAOE;

	USceneComponent* rootComponent;


	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


private:
	FVector beginLocation;
	bool hit = false;

public:	
	UFUNCTION()
	void applyDamageToWithDelay(AActor* OtherActor, float Delay);

	void applyDamageTo(AActor* OtherActor);

};
