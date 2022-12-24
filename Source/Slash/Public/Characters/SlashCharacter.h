// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CharacterTypes.h"
#include "SlashCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class AItem;
class UAnimMontage;

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

	UPROPERTY( VisibleAnywhere )
		USpringArmComponent* CameraBoom;

	UPROPERTY( VisibleAnywhere )
		UCameraComponent* ViewCamera;

	/**
	 * Callback for Input
	 */

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



	void Move( const FInputActionValue& Value );
	void Look( const FInputActionValue& Value );

	void Attack( );



	/*
	* Play Montage Functions
	*/
	 
	void PlayAttackMontage( );

	UFUNCTION(BlueprintCallable)
	void AttackEnd( );
	bool CanAttack( );

private:

	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true") )
	EActionState ActionState = EActionState::EAS_Unoccupied;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

/*
	Animation Montages
*/
	UPROPERTY(EditDefaultsOnly, Category = Montages )
	UAnimMontage* AttackMontage;

public:

	FORCEINLINE void SetOverlappingItem( AItem* Item ) { OverlappingItem = Item; }
	FORCEINLINE ECharacterState GetCharacterState( ) const { return CharacterState; }
};
