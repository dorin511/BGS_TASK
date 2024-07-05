// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SGCharacter.h"
#include "Skateboard/SGSkateboard.h"
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
}

void ASGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Skateboard = GetWorld()->SpawnActor<ASGSkateboard>(SkateboardClass, GetActorTransform());
	//if (Skateboard) this->AttachToActor(Skateboard, FAttachmentTransformRules::KeepRelativeTransform);
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
}

void ASGCharacter::MoveForward(float amount)
{
	bIsMovingForwardPressed = amount > 0;

	GEngine->AddOnScreenDebugMessage(0, 2.f, FColor::Black, FString::Printf(TEXT("%d"), bIsMovingForwardPressed));
}

void ASGCharacter::Turn(float amount)
{
	AddControllerYawInput(amount);
}

void ASGCharacter::UpdateMovementSpeed(float deltaTime)
{
	CurrentAcceleration += bIsAccelerating ? AccelerationSpeed * deltaTime : -DeccelerationSpeed * deltaTime;

	CurrentAcceleration = FMath::Clamp(CurrentAcceleration, 0.f, 1.f);

	if (bIsAccelerating) bIsAccelerating = false;
	AddMovementInput(GetActorForwardVector(), CurrentAcceleration);
}
