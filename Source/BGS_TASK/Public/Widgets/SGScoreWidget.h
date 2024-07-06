// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SGScoreWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class BGS_TASK_API USGScoreWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateScore(const int32 value);

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ScoreText;
};
