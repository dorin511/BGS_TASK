// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SGAnimInstance.generated.h"

class ASGCharacter;

/**
 * 
 */
UCLASS()
class BGS_TASK_API USGAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float deltaSeconds) override;

protected:
	void UpdatePlayerStats();

protected:
	UPROPERTY()
	ASGCharacter* Player = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float Speed = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bIsJumping = false;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bStartJumpAnim = false;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bIsMovingForwardPressed = false;
};
