// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityComponent.h"
#include "BasePlayerCharacter.h"

// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	
	if (GetOwner() && Cast<ABasePawn>(GetOwner()))
	{
		ownerCharacter = Cast<ABasePawn>(GetOwner());
		GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Green, FString::Printf(TEXT("Hello")));
	}
		
	
}


// Called every frame
void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

}

void UAbilityComponent::dodge()
{
	/*
	UAnimInstance* animInstance = ownerCharacter->GetMesh()->GetAnimInstance();
	if (animDodge && animInstance) {
		animInstance->Montage_Play(animDodge);
	}	
	*/
	UAnimInstance* animInstance = ownerCharacter->GetMesh()->GetAnimInstance();
	if (animDodge && animInstance) {
		animInstance->Montage_Play(animDodge);
	}
	if (ownerCharacter->equiptWeapon)
	{
		ownerCharacter->equiptWeapon->basicAnim = animDoubleShot;
	}
}

void UAbilityComponent::kick()
{
	UAnimInstance* animInstance = ownerCharacter->GetMesh()->GetAnimInstance();
	if (animKick && animInstance) {
		animInstance->Montage_Play(animKick);
	}
	if (ownerCharacter->equiptWeapon)
	{
		ownerCharacter->equiptWeapon->basicAnim = animDoubleShot;
	}
}

void UAbilityComponent::chargedShot()
{
	UAnimInstance* animInstance = ownerCharacter->GetMesh()->GetAnimInstance();
	if (animKick && animInstance) {
		animInstance->Montage_Play(animChargedShot);
	}
	if (ownerCharacter->equiptWeapon)
	{
		ownerCharacter->equiptWeapon->basicAnim = animDoubleShot;
	}

}

void UAbilityComponent::dashAttack()
{
	UAnimInstance* animInstance = ownerCharacter->GetMesh()->GetAnimInstance();
	if (animKick && animInstance) {
		animInstance->Montage_Play(animDashAttack);
	}

	if (ownerCharacter->equiptWeapon)
	{
		ownerCharacter->equiptWeapon->basicAnim = animWaveAttack;
	}
}

void UAbilityComponent::fireyBlade()
{
	if (ownerCharacter->equiptWeapon)
	{   
		WeaponBuffParam param{ 10.f,50.f,0.f };
		ownerCharacter->equiptWeapon->activeWeaponBuff(param);

		ownerCharacter->playAttackMontage();
	}
		
}

