// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolRoute.h"

// Sets default values
APatrolRoute::APatrolRoute()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APatrolRoute::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APatrolRoute::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APatrolRoute::incrementPatrolRoute()
{
	
	PatrolIndex = PatrolIndex + Direction;
	if (PatrolIndex == PatrolRoute->GetNumberOfSplinePoints() - 1)
	{
		Direction = -1;

	}
	else if(PatrolIndex == 0){
		Direction = 1;
	}

}

FVector APatrolRoute::getSplinePointToWorldLocation()
{
	return PatrolRoute->GetLocationAtSplinePoint(PatrolIndex, ESplineCoordinateSpace::Local);
}

