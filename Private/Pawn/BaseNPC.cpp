// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseNPC.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Item/MeleeWeapon.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

ABaseNPC::ABaseNPC()
{
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetGenerateOverlapEvents(true);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	meleeBox = CreateDefaultSubobject<UBoxComponent>(TEXT("melee box"));
	meleeBox->SetupAttachment(GetRootComponent());

}

void ABaseNPC::attack()
{
	playAttackMontage();

	
}

void ABaseNPC::charge()
{
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	UAnimMontage* animMontage = chargeAnim;
	if (animInstance && animMontage)
	{
		animInstance->Montage_Play(animMontage, attackSpeed);
		FName SectionName = FName();
		int attackRand  = 1 + (rand() % 3);
		switch (attackRand)
		{
		case 1:
			SectionName = FName("Attack1");
			break;
		case 2:
			SectionName = FName("Attack2");
			break;
		case 3:
			SectionName = FName("Attack3");
			break;
		case 4:
			SectionName = FName("Attack4");
			break;
		case 5:
			SectionName = FName("Attack5");
			break;
		default:
			break;
		}

		animInstance->Montage_JumpToSection(SectionName, animMontage);
	}
}

void ABaseNPC::dumbTrace()
{
	TArray<AActor*> victims;
	meleeBox->GetOverlappingActors(victims, ABasePawn::StaticClass());

	for (AActor* victim : victims)
	{
		if (victim->ActorHasTag(FName("human")))
		{
			ICombatInterface* combatInterface = Cast<ICombatInterface>(victim);
			if (combatInterface)
			{
				GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Green, FString::Printf(TEXT("comba")));
				if (equiptWeapon)
				{
					GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Green, FString::Printf(TEXT("weapoj")));
					combatInterface->takeDamage(GetActorLocation(), equiptWeapon->totalPhysicalDMG(), equiptWeapon->weaponPhysicalDamageType, equiptWeapon->totalMagicalDMG(), equiptWeapon->weaponMagicalDamageType, equiptWeapon->weaponBaseForce);

				}
			
			}
		}

	}
}

void ABaseNPC::takeDamage(const FVector& ImpactPoint, float physicalDamageValue, EPhysicalDamageType physicalDamageType, float magicalDamageValue, EMagicalDamageType magicalDamageType, float damageForce)
{
	Super::takeDamage(ImpactPoint, physicalDamageValue, physicalDamageType, magicalDamageValue, magicalDamageType, damageForce);

	DirectionalHitReact(ImpactPoint, damageForce);

	if (physicalDamageValue > 0)
	{
		float mitigatedPhysicalDamage = resistDamage(physicalDamageValue, physicalDefense);
		safeUpdate(currentHP, maxHP, -1 * mitigatedPhysicalDamage);
	}

	if (magicalDamageValue > 0)
	{
		float mitigatedMagicalDamage = resistDamage(magicalDamageValue, magicalDefense);
		safeUpdate(currentHP, maxHP, -1 * mitigatedMagicalDamage);
	}

	timeUntilResetPoise = poiseResetTime;
	float mitigatedPoiseDamage = resistDamage(damageForce, physicalDefense);
	safeUpdate(currentPoise, maxPoise, -1 * mitigatedPoiseDamage);



	if (sharpLightOnhitEfect != NULL)
	{
		UNiagaraComponent* effect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, sharpLightOnhitEfect, ImpactPoint, FRotator(1), FVector(1, 1, 1), true, true);
	}



}

void ABaseNPC::DirectionalHitReact(const FVector& ImpactPoint, const float damageForce)
{
	FName section = FindHitDirection(ImpactPoint);

	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	UAnimMontage* montageToPlay = NULL;
	USoundWave* audioToPlay = NULL;
	if (damageForce >= knockBackForce) {
		montageToPlay = onHitHeavyAnims;
		audioToPlay = onHitSoundMedium;
		applyStunDuration(1.0f);
	}
	else if(damageForce >= staggerForce){
		montageToPlay = onHitLightAnims;
		audioToPlay = onHitSoundLight;
		applyStunDuration(.1f);
	}
	if (animInstance && montageToPlay)
	{
		animInstance->Montage_Play(montageToPlay);
		animInstance->Montage_JumpToSection(section, montageToPlay);
	}

	if (audioToPlay)
	{
		UGameplayStatics::PlaySound2D(this, audioToPlay);
	}
}
