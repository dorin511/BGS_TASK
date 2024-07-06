// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SGScoreWidget.h"
#include "Components/TextBlock.h"

void USGScoreWidget::UpdateScore(const int32 value)
{
	ScoreText->SetText(FText::FromString(FString::FromInt(value)));
}
