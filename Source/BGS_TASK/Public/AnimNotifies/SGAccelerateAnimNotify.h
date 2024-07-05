// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SGAccelerateAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class BGS_TASK_API USGAccelerateAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation) override;
};
