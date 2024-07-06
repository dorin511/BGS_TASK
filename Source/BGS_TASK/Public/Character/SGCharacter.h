// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SGCharacter.generated.h"

class ASGSkateboard;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class BGS_TASK_API ASGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASGCharacter();

	virtual void Tick(float deltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;

	bool IsMovingForwardPressed() const { return bIsMovingForwardPressed; }

	void SetIsAccelerating(bool bValue) { bIsAccelerating = bValue; }

	bool IsJumping() const { return bIsJumping; }
	void EndJumping();

protected:
	virtual void BeginPlay() override;

	void MoveForward(float amount);
	void Turn(float amount);
	void Jump();

	void UpdateMovementSpeed(float deltaTime);

protected:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SkateComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Skateboard")
	FName JumpAttachSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Skateboard")
	float AccelerationSpeed = 10.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Skateboard")
	float DeccelerationSpeed = .05f;

	UPROPERTY(EditDefaultsOnly, Category = "Skateboard")
	float SlowDownSpeed = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Skateboard")
	float MinJumpSpeed = 400.f;

	float CurrentAcceleration = 0.f;

	bool bIsAccelerating = false;
	bool bIsSlowingDown = false;
	bool bIsMovingForwardPressed = false;
	bool bIsJumping = false;
};
