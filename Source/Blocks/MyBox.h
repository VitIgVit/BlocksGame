// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBox.generated.h"


UCLASS()
class BLOCKS_API AMyBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) class USceneComponent* DummyRoot;//переменная для корня меша

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) class UStaticMeshComponent* BlockMesh;//переменная для меша

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) class UMaterial* tempMaterial;//переменная материала

	/* Функция создания блока*/
	void CreateBlock();
	// текущий цвет материала
	UPROPERTY() int32 IndexCurrentMaterial;
	//массив списка материалов для актера
	TArray<class UMaterial*> MyListMaterial;
	//функция для загрузки списка материалов
	void LoadListMaterial();
	//Функция рандомного выбора материала
	void RandomColor(); 
	// функция для щелчка мышки по блоку
	UFUNCTION()	void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonPressed);

	// переменные для хранения позиции блока в общей сетке
	UPROPERTY() int32 X;   // Позиция по X
	UPROPERTY() int32 Y;  // Позиция по Y

	UPROPERTY() class AMyMap* OwnMap; // Карта, кто создал блок
};
