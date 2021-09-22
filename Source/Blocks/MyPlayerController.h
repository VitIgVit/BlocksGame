// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKS_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	/* «адаем свойство, которое можно будет редактировать везде*/
	bool ShowMouseCursor;
	/*  онструктор создани€ игрового мира*/
	AMyPlayerController();

private:
	/* функци€, котора€ отображает или пр€чет курсор*/
	void ShowHideCursor();


};
