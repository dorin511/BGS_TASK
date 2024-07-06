// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/SGLandAnimNotify.h"
#include "Character/SGCharacter.h"

void USGLandAnimNotify::Notify(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation)
{
	ASGCharacter* player = Cast<ASGCharacter>(meshComp->GetAttachParentActor());

	if (!player) return;
}