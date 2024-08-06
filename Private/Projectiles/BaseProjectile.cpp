// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Interface/CombatInterface.h"
// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootComponent);


	projectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	projectileMesh->SetupAttachment(rootComponent);

	projectileBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Projectile Box"));
	projectileBox->SetupAttachment(rootComponent);

	projectileAOE = CreateDefaultSubobject<USphereComponent>(TEXT("Projectile AOE"));
	projectileAOE->SetupAttachment(rootComponent);
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	beginLocation = GetActorLocation();
	projectileBox->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::OnBoxBeginOverlap);
	
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//rotate arrow mesh with velocity
	FRotator res = UKismetMathLibrary::MakeRotFromX(GetVelocity());
	projectileMesh->SetWorldRotation(res);


	float distanceTraveled = FVector::Distance(GetActorLocation(), beginLocation);

	if (distanceTraveled > projectileRange)
	{
		Destroy();
	}



}

void ABaseProjectile::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (hit || !OtherActor->ActorHasTag("enemy")) return;

	ICombatInterface* combatInterface = Cast<ICombatInterface>(OtherActor);
	if (combatInterface)
	{
		hit = true;
		applyDamageToWithDelay(OtherActor, 0.05f);
	}
}

void ABaseProjectile::applyDamageTo(AActor* OtherActor)
{
	ICombatInterface* combatInterface = Cast<ICombatInterface>(OtherActor);
	combatInterface->takeDamage(GetActorLocation(), ABaseProjectile::weaponBaseAD, ABaseProjectile::weaponPhysicalDamageType, ABaseProjectile::weaponBaseAP, ABaseProjectile::weaponMagicalDamageType, ABaseProjectile::weaponBaseForce);
	Destroy();
}

void ABaseProjectile::applyDamageToWithDelay(AActor* OtherActor, float Delay)
{
	FTimerHandle TimerHandle_DMGDelay;
	FTimerDelegate RespawnDelegate = FTimerDelegate::CreateUObject(this, &ABaseProjectile::applyDamageTo, OtherActor);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_DMGDelay, RespawnDelegate, Delay, false);
}