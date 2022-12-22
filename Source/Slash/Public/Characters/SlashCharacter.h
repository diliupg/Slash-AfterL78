// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SlashCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class AItem;

UCLASS()
class SLASH_API ASlashCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ASlashCharacter();

	UPROPERTY( EditAnywhere )
	float MaxAngle;
	UPROPERTY( EditAnywhere )
	float MinAngle;

	virtual void Tick( float DeltaTime ) override;

	virtual void SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent ) override;

	virtual void Jump( ) override;

	void EKeyPressed( );

protected:

	virtual void BeginPlay() override;

	UPROPERTY( EditAnywhere, Category = Input )
	TObjectPtr<UInputMappingContext> SlashContext;

	UPROPERTY( EditAnywhere, Category = Input )
	TObjectPtr<UInputAction> MovementAction;

	UPROPERTY( EditAnywhere, Category = Input )
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY( EditAnywhere, Category = Input )
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY( EditAnywhere, Category = Input )
	TObjectPtr<UInputAction> EKeyAction;

	UPROPERTY( EditAnywhere, Category = Input )
		TObjectPtr<UInputAction> AttackAction;

	UPROPERTY( EditAnywhere, Category = Input )
		TObjectPtr<UInputAction> DodgeAction;

	UPROPERTY( VisibleAnywhere )
	USpringArmComponent* CameraBoom;

	UPROPERTY( VisibleAnywhere )
	UCameraComponent* ViewCamera;

	void Move( const FInputActionValue& Value );
	void Look( const FInputActionValue& Value );

private:

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

public:

	FORCEINLINE void SetOverlappingItem( AItem* Item ) { OverlappingItem = Item; }
};
