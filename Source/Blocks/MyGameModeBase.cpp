// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"// �������� ��������� �����������
#include "MyGameModeBase.h"

/* ��������� ����������� ������*/
AMyGameModeBase::AMyGameModeBase()
{
	/* �� ��������� ����� ���*/
	DefaultPawnClass = NULL;
	/* ������ �������� ����������� � ������*/
	PlayerControllerClass = AMyPlayerController::StaticClass();
}