// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGSkateboard.generated.h"

UCLASS()
class BGS_TASK_API ASGSkateboard : public AActor
{
	GENERATED_BODY()
	
public:
	ASGSkateboard();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float deltaTime) override;

};
