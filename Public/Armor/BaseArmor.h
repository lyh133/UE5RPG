// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DAZUNREAL5_API BaseArmor
{
public:
	BaseArmor();
	~BaseArmor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* Appearance100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* Appearance75;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* Appearance50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* Appearance25;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxDurability = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float currDurability = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float bonusPD = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float bonusMD = 0.f;
};
