// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SGAnimInstance.h"
#include "Character/SGCharacter.h"
#include "GameFramework/PawnMovementComponent.h"

void USGAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Player = Cast<ASGCharacter>(TryGetPawnOwner());
}

void USGAnimInstance::NativeUpdateAnimation(float deltaSeconds)
{
	Super::NativeUpdateAnimation(deltaSeconds);

	UpdatePlayerStats();
}

void USGAnimInstance::UpdatePlayerStats()
{
	if (!Player) return;

	Speed = Player->GetVelocity().Size();

	bStartJumpAnim = Player->GetStartJumpAnim();

	bIsJumping = Player->GetMovementComponent()->IsFalling() || bStartJumpAnim;

	bIsMovingForwardPressed = Player->IsMovingForwardPressed();
}
