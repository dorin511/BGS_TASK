// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SGCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USphereComponent;

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

	virtual void Jump() override;
	virtual void StopJumping() override;

	bool GetStartJumpAnim() const { return bStartJumpAnim; }

protected:
	virtual void BeginPlay() override;

	void MoveForward(float amount);
	void Turn(float amount);
	
	void JumpButtonPressed();

	void UpdateMovementSpeed(float deltaTime);

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);
	
	UFUNCTION()
	void OnJumpDetectionCapsuleOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

protected:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SkateComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* JumpDetectionCapsule = nullptr;

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

	UPROPERTY(EditDefaultsOnly, Category = "Skateboard")
	float JumpCooldown = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Skateboard")
	int32 JumpScore = 100;

	float TimeFromLastJump = 1.f;
	float CurrentAcceleration = 0.f;
	float ZLocOnStartJump = 0.f;

	bool bIsAccelerating = false;
	bool bIsSlowingDown = false;
	bool bIsMovingForwardPressed = false;
	bool bStartJumpAnim = false;
	bool bIsJumping = false;

	int32 GameScore = 0;

	FVector SkateRelativeLoc;
};
