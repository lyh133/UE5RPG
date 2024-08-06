// Fill out your copyright notice in the Description page of Project Settings.


#include "RangedWeapon.h"
#include "Components/ArrowComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "BaseProjectile.h"
ARangedWeapon::ARangedWeapon()
{
	firePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Point"));
	firePoint->SetupAttachment(rootComponent);
	//TraceVFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Trace VFX"));
	//TraceVFX->SetupAttachment(rootComponent);
	//TraceVFX->DeactivateImmediate();
}


void ARangedWeapon::fire()
{
	ABaseProjectile* projectile = GetWorld()->SpawnActor<ABaseProjectile>(projectileClass, firePoint->GetComponentLocation(), firePoint->GetComponentRotation());
	InitProjectileStats(projectile);
}

void ARangedWeapon::Tracefire()
{
	//TraceVFX->ActivateSystem();
}

void ARangedWeapon::fireChargedShot()
{
	if (chargedProjectileClass)
	{
		ABaseProjectile* projectile = GetWorld()->SpawnActor<ABaseProjectile>(chargedProjectileClass, firePoint->GetComponentLocation(), firePoint->GetComponentRotation());
		InitProjectileStats(projectile);
	}

}

void ARangedWeapon::InitProjectileStats(ABaseProjectile* projectile)
{
	projectile->weaponBaseAD = totalPhysicalDMG() + projectile->projectileBaseAD + projectile->projectileADMult * getOwnerAD();
	projectile->weaponBaseAP = totalMagicalDMG() + projectile->projectileBaseAP + projectile->projectileAPMult * getOwnerAP();;
	projectile->weaponBaseForce = totalForce() + projectile->projectileBaseForce;
	projectile->weaponMagicalDamageType = weaponMagicalDamageType;
	projectile->weaponPhysicalDamageType = weaponPhysicalDamageType;
}
