// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BasePlayerCharacter.h"
// Sets default values for this component's properties
UArmorComponent::UArmorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	owner = Cast<ABasePlayerCharacter>(GetOwner());
	

}


// Called when the game starts
void UArmorComponent::BeginPlay()
{
	Super::BeginPlay();

	if (armorType == ArmorType::EA_UpperBody) {
		playerMesh = owner->Armor_body;
	}
	if (armorType == ArmorType::EA_LowerBody) {
		playerMesh = owner->Armor_lower;
	}
	onAttach();
	// ...
	
}


// Called every frame
void UArmorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UArmorComponent::onAttach()
{
	playerMesh->SetSkeletalMeshAsset(Appearance100);
	
	owner->physicalDefense += bonusPD;
	owner->magicalDefense += bonusMD;
}

void UArmorComponent::onDettach()
{

	playerMesh->SetSkeletalMeshAsset(NULL);
	owner->physicalDefense -= bonusPD;
	owner->magicalDefense -= bonusMD;
	DestroyComponent();
}

void UArmorComponent::onDamage(float dmg, EPhysicalDamageType dmgType)
{
	if (armorType == ArmorType::EA_UpperBody && onHitSound)
		UGameplayStatics::PlaySound2D(this, onHitSound);

	if (dmgType == EPhysicalDamageType::EP_BLUNT) dmg *= 2;
	currDurability -= dmg;
	if (currDurability <= 0)
	{
		onDettach();
	}
	else if ((currDurability / maxDurability) <= 0.25)
	{
		playerMesh->SetSkeletalMeshAsset(Appearance25);
	}
	else if ((currDurability / maxDurability) <= 0.5)
	{
		playerMesh->SetSkeletalMeshAsset(Appearance50);
	}
	else if ((currDurability / maxDurability) <= 0.75)
	{
		playerMesh->SetSkeletalMeshAsset(Appearance75);
	}
}

