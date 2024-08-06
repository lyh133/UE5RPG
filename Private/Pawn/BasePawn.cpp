// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

#define Delay(Duration, Looping, FuncName) FTimerHandle Handle; FTimerDelegate Delegate; Delegate.BindUFunction(this, FName(FuncName)); GetWorldTimerManager().SetTimer(Handle, Delegate, Duration, Looping)

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasePawn::playHitReactionMontage(const FName& section)
{
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	UAnimMontage* montageToPlay;
	USoundWave* audioToPlay;
	if ((currentPoise / maxPoise) > 0.5) {
		montageToPlay = onHitLightAnims;
		audioToPlay = onHitSoundLight;
	}
	else {
		montageToPlay = onHitHeavyAnims;
		audioToPlay = onHitSoundMedium;
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

void ABasePawn::safeUpdate(float& attribute, float maxAttribute, float value)
{
	if (attribute + value < 0)
	{
		attribute = 0;
	}
	else if (attribute + value > maxAttribute)
	{
		attribute = maxAttribute;
	}
	else {
		attribute = attribute + value;
	}
}

float ABasePawn::resistDamage(float dmg, float resist)
{
	if (resist >= 0)
	{
		return (100 / (100 + resist)) * dmg;
	}

	return (2 - (100 / (100 - resist))) * dmg;
	
}

void ABasePawn::takeDamage(const FVector& ImpactPoint,
	float physicalDamageValue,
	EPhysicalDamageType physicalDamageType,
	float magicalDamageValue,
	EMagicalDamageType magicalDamageType,
	float damageForce)
{
	//calculate reaction direction
	//DirectionalHitReact(ImpactPoint);

	
}

void ABasePawn::onKnockDown()
{
	isKnockDown = true;
}

FName ABasePawn::FindHitDirection(const FVector& ImpactPoint) const
{
	const FVector Forward = GetActorForwardVector();
	//lower to enemy height
	const FVector ImpactLowered(ImpactPoint.X, ImpactPoint.Y, GetActorLocation().Z);
	const FVector ToHit = (ImpactLowered - GetActorLocation()).GetSafeNormal();
	const double CosTheta = FVector::DotProduct(Forward, ToHit);
	double Theta = FMath::Acos(CosTheta);
	Theta = FMath::RadiansToDegrees(Theta);

	const FVector crossProduct = FVector::CrossProduct(Forward, ToHit);

	if (crossProduct.Z < 0)
	{
		Theta *= -1;
	}

	FName Section("FromBack");

	if (Theta >= -45.f && Theta < 45.f)
	{
		Section = FName("FromFront");
	}
	else if (Theta >= -135.f && Theta < -45.f)
	{
		Section = FName("FromLeft");
	}
	else if (Theta >= 45.f && Theta < 135.f)
	{
		Section = FName("FromRight");
	}
	return Section;

}

void ABasePawn::applyStunDuration(float duration)
{
	stun();

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &ABasePawn::unstun, duration, false);
}



// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (timeUntilResetPoise == 0) {
		currentPoise = maxPoise;
	}
	else {
		
		timeUntilResetPoise = FMath::Clamp(timeUntilResetPoise - GetWorld()->GetDeltaSeconds(), 0.f, poiseResetTime);
		
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("poise is %s"), currentPoise.ToString());

	if (currentHP <= 0) {
		Destroy();
	}

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ABasePawn::playAttackMontage()
{
	UAnimMontage* animMontage;
	int maxSeq;
	if (!equiptWeapon) {
		safeUpdate(currentStamina, maxStamina, -1 * 5);

		int montageIndex = FMath::RandRange(0, punchMontages.Num() - 1);
		animMontage = punchMontages[montageIndex];
		maxSeq = 3;
	}
	else {
		safeUpdate(currentStamina, maxStamina, -1 * equiptWeapon->staminaCost);
		animMontage = equiptWeapon->getBasicAnim();
		maxSeq = equiptWeapon->maxSeq;
	}


	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	


	if (animInstance && animMontage)
	{

		animInstance->Montage_Play(animMontage, attackSpeed);
		FName SectionName = FName();
		switch (attackSeq)
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

		if (attackSeq == maxSeq)
		{
			attackSeq = 1;
		}
		else {
			attackSeq++;
		}

	}

	FOnMontageEnded BlendOutDelegate;
	BlendOutDelegate.BindUObject(this, &ABasePawn::FunctionToExecuteOnAnimationBlendOut);
	animInstance->Montage_SetBlendingOutDelegate(BlendOutDelegate, animMontage);


	FOnMontageEnded CompleteDelegate;
	CompleteDelegate.BindUObject(this, &ABasePawn::FunctionToExecuteOnAnimationEnd);
	animInstance->Montage_SetEndDelegate(CompleteDelegate, animMontage);

}

void ABasePawn::playRAttackMontage()
{
	UAnimMontage* animMontage;
	int maxSeq;
	if (!equiptWeapon) {
		safeUpdate(currentStamina, maxStamina, -1 * 15);

		int montageIndex = FMath::RandRange(0, kickMontages.Num() - 1);
		animMontage = kickMontages[montageIndex];
		maxSeq = 3;
	}
	else {
		safeUpdate(currentStamina, maxStamina, -1 * equiptWeapon->staminaCost);
		animMontage = equiptWeapon->getRightBasicAnim();
		maxSeq = equiptWeapon->RmaxSeq;
	}


	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();



	if (animInstance && animMontage)
	{
		animInstance->Montage_Play(animMontage, attackSpeed);
		FName SectionName = FName();
		switch (attackSeq)
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

		if (attackSeq == maxSeq)
		{
			attackSeq = 1;
		}
		else {
			attackSeq++;
		}

	}
}

void ABasePawn::FunctionToExecuteOnAnimationBlendOut(UAnimMontage* animMontage, bool bInterrupted)
{
	if (bInterrupted)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("MY ANIMATION WAS INTERRUPTED!")));
		attackFinish.Broadcast();
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("MY ANIMATION IS BLENDING OUT!")));
	}
}

void ABasePawn::FunctionToExecuteOnAnimationEnd(UAnimMontage* animMontage, bool bInterrupted)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("MY ANIMATION IS COMPLETED!")));
	attackFinish.Broadcast();
}

//void ABasePawn::PlayAnAnimationMontage(UAnimMontage* montageToPlay)
//{
//	if (montageToPlay)
//	{
//		Montage_Play(montageToPlay);
//
//		FOnMontageEnded BlendOutDelegate;
//		BlendOutDelegate.BindUObject(this, &ABasePawn::FunctionToExecuteOnAnimationBlendOut);
//		Montage_SetBlendingOutDelegate(BlendOutDelegate, montageToPlay);
//
//		FOnMontageEnded CompleteDelegate;
//		CompleteDelegate.BindUObject(this, &ABasePawn::FunctionToExecuteOnAnimationEnd);
//		Montage_SetEndDelegate(CompleteDelegate, montageToPlay);
//	}
//}