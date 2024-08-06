// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AArmor.generated.h"
class ABasePlayerCharacter;
UCLASS()
class DAZUNREAL5_API AArmor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArmor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* Armor_100;


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
	void onDettach();
	void onDamage(float dmg);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	ABasePlayerCharacter* owner;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
