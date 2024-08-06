// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Item/MeleeWeapon.h"
#include "Components/BoxComponent.h"
#include "AbilityComponent.h"
#include "ArmorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "BleedEffect.h"



// Called every frame
void ABasePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	controlCamera();
	//FVector vv = getDesiredMovement();


	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("World delta for current frame equals %s"), *vv.ToString()));
	//GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Green, FString::Printf(TEXT("Hello %s"), *GetActorLocation().ToString()));
	

}


ABasePlayerCharacter::ABasePlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());

	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ThridPersonCamera"));
	ThirdPersonCamera->SetupAttachment(CameraBoom);

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetMesh());
	FirstPersonCamera->SetActive(false);
	FirstPersonCamera->bUsePawnControlRotation = true;

	abilityComponent = CreateDefaultSubobject<UAbilityComponent>(TEXT("AbilityComp"));
	//bodyArmorComponent = CreateDefaultSubobject<UArmorComponent>(TEXT("ArmorComp"));

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;


	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = movementSpeed;


	Armor_body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmorBody"));
	Armor_lower = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmorLower"));
	Armor_body->SetupAttachment(GetMesh());
	Armor_lower->SetupAttachment(GetMesh());


	characterFront = CreateDefaultSubobject<UArrowComponent>(TEXT("characterFront"));
	characterFront->SetupAttachment(GetRootComponent());

	characterBack = CreateDefaultSubobject<UArrowComponent>(TEXT("characterBack"));
	characterBack->SetupAttachment(GetRootComponent());


	kickBox = CreateDefaultSubobject<UBoxComponent>(TEXT("kickBox"));
	kickBox->SetupAttachment(GetRootComponent());

	punchBox = CreateDefaultSubobject<UBoxComponent>(TEXT("punchBox"));
	punchBox->SetupAttachment(GetRootComponent());
}

void ABasePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ABasePlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ABasePlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ABasePlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ABasePlayerCharacter::Turn);


	PlayerInputComponent->BindAxis(FName("pForward"), this, &ABasePlayerCharacter::pForward);
	PlayerInputComponent->BindAxis(FName("pLeft"), this, &ABasePlayerCharacter::pLeft);


	PlayerInputComponent->BindAction(FName("Attack"), IE_Pressed, this, &ABasePlayerCharacter::Attack);
	PlayerInputComponent->BindAction(FName("RAttack"), IE_Pressed, this, &ABasePlayerCharacter::RAttack);
	PlayerInputComponent->BindAction(FName("Attack"), IE_Released, this, &ABasePlayerCharacter::UnAttack);
	PlayerInputComponent->BindAction(FName("Jog"), IE_Pressed, this, &ABasePlayerCharacter::controlJog);
	PlayerInputComponent->BindAction(FName("Sprint"), IE_Pressed, this, &ABasePlayerCharacter::controlSprint);
	PlayerInputComponent->BindAction(FName("TogglePerspective"), IE_Pressed, this, &ABasePlayerCharacter::toggleCameraPerspective);

	PlayerInputComponent->BindAction(FName("BackDodge"), IE_Pressed, this, &ABasePlayerCharacter::BackDodge);
	PlayerInputComponent->BindAction(FName("FrontDodge"), IE_Pressed, this, &ABasePlayerCharacter::FrontDodge);
	PlayerInputComponent->BindAction(FName("LeftDodge"), IE_Pressed, this, &ABasePlayerCharacter::LeftDodge);
	PlayerInputComponent->BindAction(FName("RightDodge"), IE_Pressed, this, &ABasePlayerCharacter::RightDodge);
	

	PlayerInputComponent->BindAction(FName("AbilityF"), IE_Pressed, this, &ABasePlayerCharacter::abilityF);
	PlayerInputComponent->BindAction(FName("AbilityE"), IE_Pressed, this, &ABasePlayerCharacter::abilityE);
	PlayerInputComponent->BindAction(FName("AbilityQ"), IE_Pressed, this, &ABasePlayerCharacter::abilityQ);
}

void ABasePlayerCharacter::kickBoxTrace() const
{

	TArray<AActor*> victims;
	kickBox->GetOverlappingActors(victims, ABasePawn::StaticClass());

	for (AActor* victim : victims)
	{
		if (victim->ActorHasTag(FName("enemy")))
		{
			ICombatInterface* combatInterface = Cast<ICombatInterface>(victim);
			if (combatInterface)
			{
				combatInterface->takeDamage(GetActorLocation(), physicalPower*1.5, EPhysicalDamageType::EP_DEFAULT, 0, EMagicalDamageType::EM_DEFAULT, 100);

			

			}
		}

	}
	
}

void ABasePlayerCharacter::punchBoxTrace()
{
	TArray<AActor*> victims;
	punchBox->GetOverlappingActors(victims, ABasePawn::StaticClass());

	for (AActor* victim : victims)
	{
		if (victim->ActorHasTag(FName("enemy")))
		{
			ICombatInterface* combatInterface = Cast<ICombatInterface>(victim);
			if (combatInterface)
			{
				combatInterface->takeDamage(GetActorLocation(), physicalPower, EPhysicalDamageType::EP_DEFAULT, 0, EMagicalDamageType::EM_DEFAULT, 20);



			}
		}

	}
}

void ABasePlayerCharacter::takeDamage(const FVector& ImpactPoint, float physicalDamageValue, EPhysicalDamageType physicalDamageType, float magicalDamageValue, EMagicalDamageType magicalDamageType, float damageForce)
{
	if (isKnockDown) return;
	Super::takeDamage(ImpactPoint, physicalDamageValue, physicalDamageType, magicalDamageValue, magicalDamageType, damageForce);


	TInlineComponentArray<UArmorComponent*> armorComponets;
	GetComponents(armorComponets);

	if (physicalDamageType == EPhysicalDamageType::EP_BLEED)
	{
		directionalBleed(ImpactPoint);
	}
	else if (armorComponets.Num() == 0 && onHitBodySound )
	{

		UGameplayStatics::PlaySound2D(this, onHitBodySound);
	
		directionalBleed(ImpactPoint);

		if (physicalDamageType == EPhysicalDamageType::EP_SHARP)
		{
			physicalDamageValue *= 2;
		}




	}

	if (physicalDamageType != EPhysicalDamageType::EP_BLEED)
	{
		for (UArmorComponent* arr : armorComponets)
		{
			arr->onDamage(physicalDamageValue, physicalDamageType);
			//GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Green, FString::Printf(TEXT("Helloasdasdasdasd ")));
		}

	}
	float mitigatedPhysicalDamage = physicalDamageValue;
	if (physicalDamageValue > 0 || physicalDamageType != EPhysicalDamageType::EP_TRUE || physicalDamageType != EPhysicalDamageType::EP_BLEED)
	{
		mitigatedPhysicalDamage = resistDamage(physicalDamageValue, physicalDefense);
	}
	safeUpdate(currentHP, maxHP, -1 * mitigatedPhysicalDamage);
	if (magicalDamageValue > 0)
	{
		float mitigatedMagicalDamage = resistDamage(magicalDamageValue, magicalDefense);
		safeUpdate(currentHP, maxHP, -1 * mitigatedMagicalDamage);
	}

	if (damageForce > 0)
	{
		timeUntilResetPoise = poiseResetTime;
		float mitigatedPoiseDamage = resistDamage(damageForce, physicalDefense);
		safeUpdate(currentPoise, maxPoise, -1 * mitigatedPoiseDamage);


		DirectionalHitReact(ImpactPoint);
	}

	
}

void ABasePlayerCharacter::DirectionalHitReact(const FVector& ImpactPoint)
{

	FName section = FindHitDirection(ImpactPoint);

	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	UAnimMontage* montageToPlay;
	USoundWave* audioToPlay;
	if ((currentPoise / maxPoise) > 0.5) {
		montageToPlay = onHitLightAnims;
		audioToPlay = onHitSoundLight;
	}
	else if(currentPoise >= 10){
		montageToPlay = onHitHeavyAnims;
		audioToPlay = onHitSoundMedium;
	}
	else {
		montageToPlay = onKOAnims;
		audioToPlay = onHitSoundMedium;
		isUninterruptibleOccupied = true;
		onKnockDown();
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



void ABasePlayerCharacter::MoveForward(float Value)
{
	if (Value == 0) return;
	if (isUninterruptibleOccupied) return;
	StopAnimMontage(equiptWeapon->getBasicAnim());
	StopAnimMontage(equiptWeapon->getRightBasicAnim());
	isOccupied = false;
	const FRotator ControlRotation = GetControlRotation();
	const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value);
	if (Value <= -0.1) {
		GetCharacterMovement()->MaxWalkSpeed = movementSpeed;
		GetCharacterMovement()->MaxAcceleration = basicAcceleration;
		playerMovementState = EPlayerMovementState::EP_WAlKING;
	}
}

void ABasePlayerCharacter::MoveRight(float Value)
{
	if( Value == 0) return;
	if (isUninterruptibleOccupied) return;
	StopAnimMontage(equiptWeapon->getBasicAnim());
	StopAnimMontage(equiptWeapon->getRightBasicAnim());
	isOccupied = false;
	const FRotator ControlRotation = GetControlRotation();
	const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Value);

}


void ABasePlayerCharacter::LookUp(float Value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Green, FString::Printf(TEXT("up %f"), GetControlRotation().Pitch));

	AddControllerPitchInput(Value);

}

void ABasePlayerCharacter::Turn(float Value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Green, FString::Printf(TEXT("up %f"), Value));

	AddControllerYawInput(Value);

}

void ABasePlayerCharacter::pForward(float Value)
{
	PAngleUp += Value;
	if (PAngleUp > 1) PAngleUp = 1;
	if (PAngleUp < -2) PAngleUp = -2;
}

void ABasePlayerCharacter::pLeft(float Value)
{
	PAngleLeft += Value;
	if (PAngleLeft > 1) PAngleLeft = 1;
	if (PAngleLeft < -1) PAngleLeft = -1;
}

void ABasePlayerCharacter::controlCamera()
{
	if (lockCamera)
	{
		doLockCamera();
	}
	else
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}
}

void ABasePlayerCharacter::BackDodge()
{
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	animInstance->Montage_Play(backDodgeMontage);
}

void ABasePlayerCharacter::FrontDodge()
{
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	animInstance->Montage_Play(frontDodgeMontage);
}

void ABasePlayerCharacter::LeftDodge()
{
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	animInstance->Montage_Play(leftDodgeMontage);
}

void ABasePlayerCharacter::RightDodge()
{
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	animInstance->Montage_Play(rightDodgeMontage);
}

void ABasePlayerCharacter::updateStats()
{
	if (playerMovementState == EPlayerMovementState::EP_JOGGING && InputComponent->GetAxisValue(TEXT("MoveForward")) != 0)
	{
		safeUpdate(currentStamina, maxStamina, -2.0f);
	}
	else if (playerMovementState == EPlayerMovementState::EP_SPRINTING && InputComponent->GetAxisValue(TEXT("MoveForward")) != 0)
	{
		GetCharacterMovement()->MaxWalkSpeed = currentSprintSpeed;
		safeUpdate(currentStamina, maxStamina, -5.0f);
	}
	else if(playerActionState == EPlayerActionState::EP_UNOCCUPIED){
		safeUpdate(currentStamina, maxStamina, staminaRegen);
	}

	if (currentStamina < 10.f)
	{
		GetCharacterMovement()->MaxWalkSpeed = movementSpeed;
		GetCharacterMovement()->MaxAcceleration = basicAcceleration;
		playerMovementState = EPlayerMovementState::EP_WAlKING;
	}
	else if ((currentStamina / maxStamina ) < 0.5f)
	{
		currentSprintSpeed = sprintSpeed * 0.5f;
	}
	else if ((currentStamina / maxStamina) < 0.8f)
	{
		currentSprintSpeed = sprintSpeed * 0.8f;
	}


	safeUpdate(currentMana, maxMana, manaRegen);

	safeUpdate(EcurrCD, EMaxCD, cdFillRate);
	safeUpdate(FcurrCD, FMaxCD, cdFillRate);
	safeUpdate(QcurrCD, QMaxCD, cdFillRate);
}

void ABasePlayerCharacter::resetAttack()
{
	canAttack = true;
	playerActionState = EPlayerActionState::EP_UNOCCUPIED;
}




void ABasePlayerCharacter::directionalBleed(const FVector& ImpactPoint)
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
		if (sharpLightOnhitEfect != NULL)
		{
			UNiagaraComponent* effect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, sharpLightOnhitEfect, characterFront->GetComponentLocation(), FRotator(1), FVector(1, 1, 1), true, true);
		}
	}
	else if (Theta >= -135.f && Theta < -45.f)
	{
		Section = FName("FromLeft");
	}
	else if (Theta >= 45.f && Theta < 135.f)
	{
		Section = FName("FromRight");
	}
	else {
		if (sharpLightOnhitEfect != NULL)
		{
			UNiagaraComponent* effect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, sharpLightOnhitEfect, characterBack->GetComponentLocation(), FRotator(1), FVector(1, 1, 1), true, true);
		}
	}
}

void ABasePlayerCharacter::doLockCamera()
{
	GetCharacterMovement()->bOrientRotationToMovement = false;
	FRotator current = GetActorRotation();
	FRotator target = FRotator(0.f, GetControlRotation().Yaw, 0.f);
	float worldDeltaSecond = GetWorld()->GetDeltaSeconds();
	FRotator res = UKismetMathLibrary::RInterpTo(current, target, worldDeltaSecond, 10);
	SetActorRotation(res);
}

void ABasePlayerCharacter::toggleCameraPerspective()
{
	if (FirstPersonCamera->IsActive())
	{
		FirstPersonCamera->SetActive(false);
		ThirdPersonCamera->SetActive(true);
		bUseControllerRotationYaw = true;
		GetMesh()->UnHideBoneByName(FName("neckLower"));
	}
	else {
		FirstPersonCamera->SetActive(true);
		ThirdPersonCamera->SetActive(false);
		bUseControllerRotationYaw = false;
		GetMesh()->HideBoneByName(FName("neckLower"), EPhysBodyOp::PBO_None);
	}
}


FVector ABasePlayerCharacter::getDesiredMovementC()
{
	const FRotator ControlRotation = GetControlRotation();
	
	FVector forwardVec = UKismetMathLibrary::GetForwardVector(FRotator(0.f, 0.f, ControlRotation.Yaw));
	float fowardValue = InputComponent->GetAxisValue(TEXT("MoveForward"));
	FVector forwardRes = forwardVec* fowardValue;

	FVector rightVec = UKismetMathLibrary::GetRightVector(FRotator(0.f, 0.f, ControlRotation.Yaw));
	float rightValue = InputComponent->GetAxisValue(TEXT("MoveRight"));
	FVector rightRes = rightVec * rightValue;

	FVector result = (rightRes + forwardRes);
	result.Normalize(0.0001);
	return result;
}

void ABasePlayerCharacter::Attack()
{
	//if (currentStamina < 20) return;
	//if (canAttack) {
	//	playerActionState = EPlayerActionState::EP_ATTACKING;
	//	canAttack = false;
	//	playAttackMontage();
	//	safeUpdate(currentStamina, maxStamina, -1 * equiptWeapon->staminaCost);

	//FTimerHandle UniqueHandle;
	//	FTimerDelegate resetAttackDel = FTimerDelegate::CreateUObject(this, &ABasePlayerCharacter::resetAttack);
	//
	//	GetWorldTimerManager().SetTimer(UniqueHandle, resetAttackDel, equiptWeapon->attackCD, false);

	//}
	//isAttacking = true;



	if (currentStamina < 20) return;
	if (!isOccupied) {
		playAttackMontage();

	}

	//UBleedEffect* NewComp = NewObject<UBleedEffect>(this);
	//NewComp->strength = 1;
	//NewComp->isTicking = true;
	//NewComp->isTimed = true;
	//NewComp->duration = 30.f;
	//NewComp->activeEffect();


}

void ABasePlayerCharacter::RAttack()
{
	if (currentStamina < 20) return;
	if (!isOccupied) {
		playRAttackMontage();

	}
}

void ABasePlayerCharacter::UnAttack()
{
	isAttacking = false;
}

void ABasePlayerCharacter::controlJog()
{
	if(currentStamina < 10) return;
	
	if (playerMovementState == EPlayerMovementState::EP_WAlKING || playerMovementState == EPlayerMovementState::EP_SPRINTING)
	{
		GetCharacterMovement()->MaxWalkSpeed = jogSpeed;
		GetCharacterMovement()->MaxAcceleration = jogAcceleration;
		playerMovementState = EPlayerMovementState::EP_JOGGING;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = movementSpeed;
		GetCharacterMovement()->MaxAcceleration = basicAcceleration;
		playerMovementState = EPlayerMovementState::EP_WAlKING;
	}
}

void ABasePlayerCharacter::controlSprint()
{
	if (currentStamina < 10) return;
	if (playerMovementState == EPlayerMovementState::EP_WAlKING || playerMovementState == EPlayerMovementState::EP_JOGGING)
	{
		GetCharacterMovement()->MaxWalkSpeed = currentSprintSpeed;
		GetCharacterMovement()->MaxAcceleration = sprintAcceleration;
		playerMovementState = EPlayerMovementState::EP_SPRINTING;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = movementSpeed;
		GetCharacterMovement()->MaxAcceleration = basicAcceleration;
		playerMovementState = EPlayerMovementState::EP_WAlKING;
	}
}

void ABasePlayerCharacter::abilityF()
{
	if (FcurrCD != FMaxCD) return;
	if (ActorHasTag("amelia"))
	{
		if (currentMana > 40)
		{
			abilityComponent->dodge();
			safeUpdate(currentMana, maxMana, -1 * 40);
		}

	}
	else if (ActorHasTag("lara"))
	{
		if (currentStamina > 40)
		{
			abilityComponent->dashAttack();
			safeUpdate(currentMana, maxMana, -1 * 40);
		}
	}
	FcurrCD = 0;
}

void ABasePlayerCharacter::abilityE()
{
	if (EcurrCD != EMaxCD) return;

	if (ActorHasTag("amelia"))
	{
		if (currentStamina > 20)
		{
			safeUpdate(currentMana, maxMana, -1 * 20);
			abilityComponent->kick();
		}
				
	}
	else if (ActorHasTag("lara"))
	{
		if (currentStamina > 20)
		{
			safeUpdate(currentMana, maxMana, -1 * 20);
			abilityComponent->fireyBlade();
		}
		
	}
		
	EcurrCD = 0;
	
}

void ABasePlayerCharacter::abilityQ()
{
	if (QcurrCD != QMaxCD) return;
	if (ActorHasTag("amelia"))
	{


		if (currentStamina > 20)
		{
			safeUpdate(currentMana, maxMana, -1 * 20);
			abilityComponent->chargedShot();
		}
		

	}
	QcurrCD = 0;
}

void ABasePlayerCharacter::basicPunch()
{
	if (currentStamina > 20)
	{
		safeUpdate(currentMana, maxMana, -1 * 20);

		//UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
		//if (animKick && animInstance) {
		//	animInstance->Montage_Play(animKick);
		//}
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%d"), punchMontages.Num()));
	}
}

void ABasePlayerCharacter::enableWeaponCollision(ECollisionEnabled::Type CollisionEnabled)
{
	if (equiptWeapon)
	{
		if (AMeleeWeapon* meleeWeapon = Cast<AMeleeWeapon >(equiptWeapon))
		{
			
			UBoxComponent* weaponBox = meleeWeapon->GetWeaponBox();
			if (weaponBox)
			{
				weaponBox->SetCollisionEnabled(CollisionEnabled);
				meleeWeapon->ignoreActors.Empty();
				
			}
			
		}
	}
}





