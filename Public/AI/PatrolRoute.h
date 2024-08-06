// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "PatrolRoute.generated.h"

UCLASS()
class DAZUNREAL5_API APatrolRoute : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APatrolRoute();
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USplineComponent* PatrolRoute;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int PatrolIndex;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int Direction;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void incrementPatrolRoute();
	UFUNCTION(BlueprintCallable)
	FVector getSplinePointToWorldLocation();

};
