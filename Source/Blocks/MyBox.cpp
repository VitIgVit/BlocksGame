// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBox.h"
#include "MyMap.h"

// Sets default values
AMyBox::AMyBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// создаем блок
	CreateBlock();
	// вызываем функцию со всеми материалами
	LoadListMaterial();
}

// Called when the game starts or when spawned
void AMyBox::BeginPlay()
{
	Super::BeginPlay();
	// при старте функция задает рандомный цвет материала
	RandomColor();
	
}

// Called every frame
void AMyBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// каждый тик обновляет цвет материала
	BlockMesh->SetMaterial(0, MyListMaterial[IndexCurrentMaterial]);
}

void AMyBox::CreateBlock()
{
	// присваиваем рут компонент
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;
	//присваиваем статик мешь
	class UStaticMesh* BlockStaticMesh = ConstructorHelpers::FObjectFinderOptional<UStaticMesh>(TEXT("StaticMesh'/Game/Cube.Cube'")).Get();
	BlockMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(BlockStaticMesh);
	//на мешь натяшиваем материал
	tempMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("Material'/Game/RedMat.RedMat'")).Get();//присваиваем материал
	BlockMesh->SetMaterial(0, tempMaterial);
	//мешь прикрепляем к корневой точке
	BlockMesh->AttachTo(DummyRoot);
	// по клику мышки меняем цвет блока
	BlockMesh->OnClicked.AddDynamic(this, &AMyBox::BlockClicked);/*Начиная с UE 4.12, ваш обработчик событий должен быть определен так,
																 чтобы принимать дополнительный параметр FKey.«События OnClick / OnReleased
																 теперь имеют дополнительный аргумент, указывающий, какой ключ был ответственен за событие»*/
}

// функция для добавления всех материалов
void AMyBox::LoadListMaterial() 
{
	tempMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("Material'/Game/TransperentMat.TransperentMat'")).Get();
	MyListMaterial.Add(tempMaterial);// добавляем материал в массив 

	tempMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("Material'/Game/BlueMat.BlueMat'")).Get();
	MyListMaterial.Add(tempMaterial);// добавляем материал в массив 

	tempMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("Material'/Game/RedMat.RedMat'")).Get();
	MyListMaterial.Add(tempMaterial);// добавляем материал в массив 

	tempMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("Material'/Game/WhiteMat.WhiteMat'")).Get();
	MyListMaterial.Add(tempMaterial);// добавляем материал в массив 

	tempMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("Material'/Game/YellowMat.YellowMat'")).Get();
	MyListMaterial.Add(tempMaterial);// добавляем материал в массив 
}

// функция генерации рандомного цвета
void AMyBox::RandomColor()
{
	// получаем размер массива из блока
	int32 ListMaterialLengh = MyListMaterial.Num() - 1;
	//задаем случайный цвет блока от 1 до размера массива блока -1
	IndexCurrentMaterial = FMath::RandRange(1, ListMaterialLengh);
}

// функция для щелчка мышки по блоку
void AMyBox::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonPressed)
{
	// При щелчке меняется цвет
	//RandomColor();
	OwnMap->SelectBlock(X, Y);
}

