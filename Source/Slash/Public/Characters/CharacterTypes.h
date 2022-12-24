#pragma once

UENUM( BlueprintType )
enum class ECharacterState : uint8
{
	ECS_Unequipped UMETA( DisplayeName = "Unequipped" ),
	ECS_EquippedOneHandedWeapon UMETA( DisplayeName = "EquippedOneHanded" ),
	ECS_EquippedTwoHandedWeapon UMETA( DisplayeName = "EquippedTwoHanded" )
};

enum class EActionState : uint8 
{
	EAS_Unoccupied UMETA(DisplayName = "Unoccupied" ),
	EAS_Attacking UMETA(DisplayName = "Attacking" )
};