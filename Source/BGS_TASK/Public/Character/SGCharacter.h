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

protected:
	virtual void BeginPlay() override;

	void MoveForward(float amount);
	void Turn(float amount);

	void UpdateMovementSpeed(float deltaTime);

protected:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Skateboard")
	TSubclassOf<ASGSkateboard> SkateboardClass = nullptr;

	UPROPERTY()
	ASGSkateboard* Skateboard = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Skateboard")
	float AccelerationSpeed = 10.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Skateboard")
	float DeccelerationSpeed = .05f;

	float CurrentAcceleration = 0.f;

	bool bIsAccelerating = false;
	bool bIsMovingForwardPressed = false;
};
