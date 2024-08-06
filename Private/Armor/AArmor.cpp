// Fill out your copyright notice in the Description page of Project Settings.


#include "AArmor.h"
#include "BasePlayerCharacter.h"

// Sets default values
AArmor::AArmor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	owner = Cast<ABasePlayerCharacter>(GetOwner());
	Armor_100 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Armor_100"));
	Armor_100->SetupAttachment(GetRootComponent());
}

void AArmor::onAttach()
{
	if (owner && owner->Armor_body)
	{
		owner->Armor_body = Armor_100;
	}
	
	//owner->physicalDefense += bonusPD;
	//owner->magicalDefense += bonusMD;
}

void AArmor::onDettach()
{
}

void AArmor::onDamage(float dmg)
{
}

// Called when the game starts or when spawned
void AArmor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArmor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

