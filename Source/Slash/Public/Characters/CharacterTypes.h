#pragma once

UENUM( BlueprintType )
enum class ECharacterState : uint8
{
	ECS_Unequipped UMETA( DisplayeName = "Unequipped" ),
	ECS_EquippedOneHandedWeapon UMETA( DisplayeName = "EquippedOneHanded" ),
	ECS_EquippedTwoHandedWeapon UMETA( DisplayeName = "EquippedTwoHanded" )
};
