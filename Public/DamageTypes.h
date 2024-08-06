#pragma once

UENUM(BlueprintType)
enum class EPhysicalDamageType : uint8
{
	EP_DEFAULT,
	EP_BLUNT,
	EP_SHARP,
	EP_BLEED,
	EP_TRUE,

};

UENUM(BlueprintType)
enum class EMagicalDamageType : uint8
{
	EM_DEFAULT,
	EM_BLEED,
	EM_POISION,
	EM_FIRE,
	EM_COROSIVE,
	EM_RADIATION
};