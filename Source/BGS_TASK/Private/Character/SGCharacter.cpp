// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SGCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

ASGCharacter::ASGCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	SkateComponent = CreateDefaultSubobject<UStaticMeshComponent>("SkateComponent");
	SkateComponent->SetupAttachment(GetMesh());

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetupAttachment(RootComponent);
	
	JumpDetectionCapsule = CreateDefaultSubobject<UCapsuleComponent>("JumpDetectionCapsule");
	JumpDetectionCapsule->SetupAttachment(RootComponent);
}

void ASGCharacter::BeginPlay()
{
	Super::BeginPlay();

	SkateRelativeLoc = SkateComponent->GetRelativeLocation();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ASGCharacter::OnSphereBeginOverlap);
	JumpDetectionCapsule->OnComponentBeginOverlap.AddDynamic(this, &ASGCharacter::OnJumpDetectionCapsuleOverlap);
}

void ASGCharacter::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	UpdateMovementSpeed(deltaTime);

	if (!bIsJumping && TimeFromLastJump < JumpCooldown)
	{
		TimeFromLastJump += deltaTime;
	}
}

void ASGCharacter::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);

	playerInputComponent->BindAxis("Forward", this, &ASGCharacter::MoveForward);
	playerInputComponent->BindAxis("Turn", this, &ASGCharacter::Turn);
	playerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ASGCharacter::JumpButtonPressed);
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

void ASGCharacter::JumpButtonPressed()
{
	if (MinJumpSpeed > GetVelocity().Size() || TimeFromLastJump < JumpCooldown) return;

	bStartJumpAnim = true;
	bIsJumping = true;
}

void ASGCharacter::Jump()
{
	bIsMovingForwardPressed = false;
	bIsSlowingDown = false;
	bStartJumpAnim = false;

	TimeFromLastJump = 0.f;

	SkateComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, JumpAttachSocketName);

	Super::Jump();
}

void ASGCharacter::StopJumping()
{
	SkateComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	SkateComponent->SetRelativeLocation(SkateRelativeLoc);

	bIsJumping = false;

	Super::StopJumping();
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

void ASGCharacter::OnSphereBeginOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (otherActor == this) return;

	CurrentAcceleration = 0.f;
}

void ASGCharacter::OnJumpDetectionCapsuleOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (otherActor == this || !bIsJumping) return;

	GameScore += JumpScore;

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Black, FString::Printf(TEXT("%d"), GameScore), false);
}
