// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

AMyPlayerController::AMyPlayerController()
{
	/* Включаем курсор*/
	ShowMouseCursor = true;
	/* Запускаем функцию*/
	ShowHideCursor();
}

void AMyPlayerController::ShowHideCursor()
{
	if (ShowMouseCursor)
	{
		bShowMouseCursor = true;//включаем показ курсора
		bEnableClickEvents = true;//разрешаем событие шелчок мышкой по объектам
		DefaultMouseCursor = EMouseCursor::Hand;//задаем изображение курсора
	}
	else
	{
		bShowMouseCursor = false;//выключаем показ курсора
		bEnableClickEvents = false;//рапрещаем событие шелчок мышкой по объектам
		DefaultMouseCursor = EMouseCursor::Hand;//задаем изображение курсора
	}
}
