#pragma once

UENUM(BlueprintType)
enum class EPlayerActionState : uint8
{
	EP_UNOCCUPIED,
	EP_ATTACKING,
};

UENUM(BlueprintType)
enum class EPlayerMovementState : uint8
{
	EP_JOGGING,
	EP_SPRINTING,
	EP_WAlKING,
	EP_INJURED
};

