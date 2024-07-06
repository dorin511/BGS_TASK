// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SGCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"

ASGCharacter::ASGCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	SkateComponent = CreateDefaultSubobject<UStaticMeshComponent>("SkateComponent");
	SkateComponent->SetupAttachment(GetMesh());
}

void ASGCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASGCharacter::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	UpdateMovementSpeed(deltaTime);
}

void ASGCharacter::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);

	playerInputComponent->BindAxis("Forward", this, &ASGCharacter::MoveForward);
	playerInputComponent->BindAxis("Turn", this, &ASGCharacter::Turn);
	playerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ASGCharacter::Jump);
}

void ASGCharacter::MoveForward(float amount)
{
	if (bIsJumping) return;

	bIsMovingForwardPressed = amount > 0;
	bIsSlowingDown = amount < 0.f;
}

void ASGCharacter::Turn(float amount)
{
	if (bIsJumping) return;

	AddControllerYawInput(amount);
}

void ASGCharacter::Jump()
{
	if (MinJumpSpeed > GetVelocity().Size() || bIsJumping) return;

	bIsJumping = true;
	bIsMovingForwardPressed = false;
	bIsSlowingDown = false;

	SkateComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, JumpAttachSocketName);
}

void ASGCharacter::EndJumping()
{
	bIsJumping = false;
	SkateComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
}

void ASGCharacter::UpdateMovementSpeed(float deltaTime)
{
	if (bIsSlowingDown) bIsAccelerating = false;

	CurrentAcceleration += bIsAccelerating ? AccelerationSpeed * deltaTime : -DeccelerationSpeed * deltaTime;
	if (bIsSlowingDown) CurrentAcceleration -= SlowDownSpeed * deltaTime;

	CurrentAcceleration = FMath::Clamp(CurrentAcceleration, 0.f, 1.f);

	if (bIsAccelerating) bIsAccelerating = false;
	AddMovementInput(GetActorForwardVector(), CurrentAcceleration);
}
