// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyMap.generated.h"

UCLASS()
class BLOCKS_API AMyMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyMap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// обьявляем точку отсчета создания игрового поля
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MySpawnPoint", meta = (AllowPrivateAccess = "true")) class UBoxComponent* SpawnPoint;
	// объявляем функцию, которая будет создавать поле во время старта игры
	void GenerateMap();

	// Функция, которая будет получать координаты блока,на которую нажал игрок
	UFUNCTION() void SelectBlock(int32 X, int32 Y);

	//Cдвигает блоки вниз во время обновления
	void MoveBlockDown();

	//Функция проверки пустых блоков
	bool SearchZeroBlock();

	//Тeкст с колличеством очков опыта
	class UTextRenderComponent* MyScoreText;

	//Функция создания текста
	void CreateMyscoreText();

	//Колличество очков
	int32 ScorePlayer = 0;
};
