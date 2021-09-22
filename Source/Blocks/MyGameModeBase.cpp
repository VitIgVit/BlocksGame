// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"// Добавляю заголовок контроллера
#include "MyGameModeBase.h"

/* Описываем конструктор класса*/
AMyGameModeBase::AMyGameModeBase()
{
	/* По умолчанию пешки нет*/
	DefaultPawnClass = NULL;
	/* Задаем значение контроллера в геймод*/
	PlayerControllerClass = AMyPlayerController::StaticClass();
}