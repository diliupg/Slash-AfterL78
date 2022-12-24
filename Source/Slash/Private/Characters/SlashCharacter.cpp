// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SlashCharacter.h"

#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Items/Item.h"
#include "Items/Weapons/Weapon.h"
#include "Animation/AnimMontage.h"


// Sets default values
ASlashCharacter::ASlashCharacter():
	MaxAngle( -45.f ),
	MinAngle( 45.f )
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement( )->bOrientRotationToMovement = true;
	GetCharacterMovement( )->RotationRate = FRotator( 0.f, 400.f, 0.f );

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>( TEXT( "CameraBoom" ) );
	CameraBoom->SetupAttachment( GetRootComponent( ) );
	CameraBoom->TargetArmLength = 300.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>( TEXT( "ViewCamera" ) );
	ViewCamera->SetupAttachment( CameraBoom );
}

void ASlashCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>( GetController( ) );
	if ( PlayerController )
	{
		// set camera pitch
		PlayerController->PlayerCameraManager->ViewPitchMin = MaxAngle; // Use whatever values you want
		PlayerController->PlayerCameraManager->ViewPitchMax = MinAngle;

		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>( PlayerController->GetLocalPlayer( ) );
		if ( Subsystem )
		{
			Subsystem->AddMappingContext( SlashContext, 0 );
		}
	} 
}


void ASlashCharacter::Move( const FInputActionValue& Value )
{
	if ( ActionState == EActionState::EAS_Attacking ) return;

	const FVector2D MovementVector = Value.Get<FVector2D>( );

	const FRotator Rotation = Controller->GetControlRotation( );
	const FRotator YawRotation( 0.f, Rotation.Yaw, 0.f );

	const FVector ForwardDirection = FRotationMatrix( YawRotation ).GetUnitAxis( EAxis::X );
	AddMovementInput( ForwardDirection, MovementVector.Y );
	const FVector RightDirection = FRotationMatrix( YawRotation ).GetUnitAxis( EAxis::Y );
	AddMovementInput( RightDirection, MovementVector.X );

}

void ASlashCharacter::Look( const FInputActionValue& Value )
{
	if ( ActionState == EActionState::EAS_Attacking ) return;

	const FVector2D LookAxisVector = Value.Get<FVector2D>( );

	AddControllerPitchInput( LookAxisVector.Y );
	AddControllerYawInput( LookAxisVector.X );
}

void ASlashCharacter::Attack( )
{	
	if ( CanAttack())
	{
		PlayAttackMontage( );
		ActionState = EActionState::EAS_Attacking;
	}
}

bool ASlashCharacter::CanAttack( )
{
	return ActionState == EActionState::EAS_Unoccupied &&
		CharacterState != ECharacterState::ECS_Unequipped;
}


void ASlashCharacter::PlayAttackMontage( )
{
	UAnimInstance* AnimInstance = GetMesh( )->GetAnimInstance( );
	if ( AnimInstance && AttackMontage )
	{
		AnimInstance->Montage_Play( AttackMontage );
		const int32 Selection = FMath::RandRange( 0, 1 );
		FName SectionName = FName( );
		switch ( Selection )
		{
		case 0:
			SectionName = FName( "Attack1" );
			break;
		case 1:
			SectionName = FName( "Attack2" );
			break;
		default:
			break;
		}
		AnimInstance->Montage_JumpToSection( SectionName, AttackMontage );
	}
}

void ASlashCharacter::AttackEnd( )
{
	ActionState = EActionState::EAS_Unoccupied;
}

void ASlashCharacter::Jump( )
{
	Super::Jump( );
}

void ASlashCharacter::EKeyPressed( )
{
	AWeapon* OverlappingWeapon = Cast<AWeapon>( OverlappingItem );
	if ( OverlappingItem )
	{
		OverlappingWeapon->Equip( GetMesh( ), FName( "RightHandSocket" ) );
		CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
	}
}

void ASlashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASlashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if ( UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>( PlayerInputComponent ) )
	{
		EnhancedInputComponent->BindAction( MovementAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Move );
		EnhancedInputComponent->BindAction( LookAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Look );
		EnhancedInputComponent->BindAction( JumpAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Jump );
		EnhancedInputComponent->BindAction( EKeyAction, ETriggerEvent::Triggered, this, &ASlashCharacter::EKeyPressed );
		EnhancedInputComponent->BindAction( AttackAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Attack );
		//EnhancedInputComponent->BindAction( DodgeAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Dodge );
	}
}


