#pragma once

UENUM( BlueprintType )
enum class ECharacterState : uint8
{
	ECS_Unequipped UMETA( DisplayeName = "Unequipped" ),
	ECS_EquippedOneHandedWeapon UMETA( DisplayeName = "EquippedOneHanded" ),
	ECS_EquippedTwoHandedWeapon UMETA( DisplayeName = "EquippedTwoHanded" )
};

UENUM( BlueprintType )
enum class EActionState : uint8 
{
	EAS_Unoccupied UMETA(DisplayName = "Unoccupied" ),
	EAS_Attacking UMETA(DisplayName = "Attacking" ),
	EAS_EquippingWeapon UMETA( DisplayName = "EquippingWeapon" )
};