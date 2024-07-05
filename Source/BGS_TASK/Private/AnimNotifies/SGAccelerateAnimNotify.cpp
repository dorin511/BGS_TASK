// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/SGAccelerateAnimNotify.h"
#include "Character/SGCharacter.h"

void USGAccelerateAnimNotify::Notify(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation)
{
	ASGCharacter* player = Cast<ASGCharacter>(meshComp->GetAttachParentActor());

	if (!player) return;

	player->SetIsAccelerating(true);
}
