// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/SGStartJumpAnimNotify.h"
#include "Character/SGCharacter.h"

void USGStartJumpAnimNotify::Notify(USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation)
{
	ASGCharacter* player = Cast<ASGCharacter>(meshComp->GetAttachParentActor());

	if (!player) return;

	player->Jump();
}