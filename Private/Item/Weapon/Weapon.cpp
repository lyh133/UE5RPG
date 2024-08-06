// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "BasePawn.h"

AWeapon::AWeapon()
{
	rootComponent  = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(rootComponent);


	weaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	weaponMesh->SetupAttachment(rootComponent);
	weaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	weaponVFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Weapon VFX"));
	weaponVFX->SetupAttachment(rootComponent);
	weaponVFX->DeactivateImmediate();
}


void AWeapon::activeWeaponBuff(WeaponBuffParam param)
{
	weaponVFX->ActivateSystem();
	weaponBaseAD += param.basePhysicalInc;
	weaponBaseAP += param.baseMagicInc;

	FTimerHandle TimerHandle_DMGDelay;
	FTimerDelegate deactiveDelegate = FTimerDelegate::CreateUObject(this, &AWeapon::deactiveWeaponBuff, param);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_DMGDelay, deactiveDelegate, param.duration, false);



}

void AWeapon::deactiveWeaponBuff(WeaponBuffParam param)
{
	weaponVFX->DeactivateImmediate();
	weaponBaseAD -= param.basePhysicalInc;
	weaponBaseAP -= param.baseMagicInc;
}



UAnimMontage* AWeapon::getBasicAnim()
{
	return basicAnim;
}

UAnimMontage* AWeapon::getRightBasicAnim()
{
	return RightBasicAnim;
}

float AWeapon::totalPhysicalDMG()
{
	AActor* owner = GetOwner();
	if (!owner) return 0.0f;

	ABasePawn* ownerBase = Cast<ABasePawn>(owner);
	if (!ownerBase) return 0.0f;

	float ownerAD = ownerBase->physicalPower;

	return weaponBaseAD + weaponADMultipler * ownerAD;
}

float AWeapon::totalMagicalDMG()
{
	AActor* owner = GetOwner();
	if (!owner) return 0.0f;

	ABasePawn* ownerBase = Cast<ABasePawn>(owner);
	if (!ownerBase) return 0.0f;

	float ownerAP = ownerBase->magicalPower;

	return weaponBaseAP + weaponAPMultipler * ownerAP;
}

float AWeapon::totalForce()
{
	AActor* owner = GetOwner();
	if (!owner) return 0.0f;

	ABasePawn* ownerBase = Cast<ABasePawn>(owner);
	if (!ownerBase) return 0.0f;

	float ownerAD = ownerBase->physicalPower;

	return weaponBaseForce + weaponForceMultiplier * ownerAD;
}

float AWeapon::getOwnerAD()
{
	AActor* owner = GetOwner();
	if (!owner) return 0.0f;
	ABasePawn* ownerBase = Cast<ABasePawn>(owner);
	if (!ownerBase) return 0.0f;

	return ownerBase->physicalPower;
}

float AWeapon::getOwnerAP()
{
	AActor* owner = GetOwner();
	if (!owner) return 0.0f;
	ABasePawn* ownerBase = Cast<ABasePawn>(owner);
	if (!ownerBase) return 0.0f;

	return ownerBase->magicalPower;
}
