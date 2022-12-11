// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SlashCharacter.h"

#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ASlashCharacter::ASlashCharacter()
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
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>( PlayerController->GetLocalPlayer( ) );
		if ( Subsystem )
		{
			Subsystem->AddMappingContext( SlashContext, 0 );
		}
	} 
}


void ASlashCharacter::Move( const FInputActionValue& Value )
{
	const FVector2D MovementVector = Value.Get<FVector2D>( );

	/*const FVector Forward = GetActorForwardVector( );
	AddMovementInput( Forward, MovementVector.Y );
	const FVector Right = GetActorRightVector( );
	AddMovementInput( Right, MovementVector.X  );*/

	const FRotator Rotation = Controller->GetControlRotation( );
	const FRotator YawRotation( 0.f, Rotation.Yaw, 0.f );

	const FVector ForwardDirection = FRotationMatrix( YawRotation ).GetUnitAxis( EAxis::X );
	AddMovementInput( ForwardDirection, MovementVector.Y );
	const FVector RightDirection = FRotationMatrix( YawRotation ).GetUnitAxis( EAxis::Y );
	AddMovementInput( RightDirection, MovementVector.X );


}

void ASlashCharacter::Look( const FInputActionValue& Value )
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>( );

	AddControllerPitchInput( LookAxisVector.Y );
	AddControllerYawInput( LookAxisVector.X );
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

	}
}
