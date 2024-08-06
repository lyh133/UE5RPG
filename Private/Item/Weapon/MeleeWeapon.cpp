// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/MeleeWeapon.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "BaseNPC.h"
AMeleeWeapon::AMeleeWeapon()
{
	weaponBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Box"));
	weaponBox->SetupAttachment(rootComponent);
	weaponBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	weaponBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	weaponBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	weaponTop = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Top"));
	weaponTop->SetupAttachment(rootComponent);

	weaponBot = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Bot"));
	weaponBot->SetupAttachment(rootComponent);
	
}


void AMeleeWeapon::OnBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

		const FVector Start = weaponTop->GetComponentLocation();
		const FVector End = weaponBot->GetComponentLocation();

		FHitResult BoxHit;
		TArray<AActor*> ActorsToIgnore;

		for (AActor* actor : ignoreActors)
		{
			ActorsToIgnore.Add(actor);
		}

		UKismetSystemLibrary::BoxTraceSingle(
			this,
			Start,
			End,
			FVector(5.f,5.f,5.f),
			weaponTop->GetComponentRotation(),
			ETraceTypeQuery::TraceTypeQuery1,
			false,
			ActorsToIgnore,
			EDrawDebugTrace::None,
			BoxHit,
			true
			);
		if (BoxHit.GetActor())
		{
			ICombatInterface* combatInterface = Cast<ICombatInterface>(BoxHit.GetActor());
			if (combatInterface)
			{
				UGameplayStatics::PlaySoundAtLocation(this, onHitSound, GetActorLocation());
				combatInterface->takeDamage(BoxHit.ImpactPoint, totalPhysicalDMG(), weaponPhysicalDamageType, totalMagicalDMG(), weaponMagicalDamageType, totalForce());
			}
			ignoreActors.AddUnique(BoxHit.GetActor());
		}
	

}



void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
	weaponBox->OnComponentBeginOverlap.AddDynamic(this, &AMeleeWeapon::OnBoxOverlap);
}
