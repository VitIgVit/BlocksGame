// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBox.h"
#include "MyMap.h"

// Sets default values
AMyBox::AMyBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ������� ����
	CreateBlock();
	// �������� ������� �� ����� �����������
	LoadListMaterial();
}

// Called when the game starts or when spawned
void AMyBox::BeginPlay()
{
	Super::BeginPlay();
	// ��� ������ ������� ������ ��������� ���� ���������
	RandomColor();
	
}

// Called every frame
void AMyBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// ������ ��� ��������� ���� ���������
	BlockMesh->SetMaterial(0, MyListMaterial[IndexCurrentMaterial]);
}

void AMyBox::CreateBlock()
{
	// ����������� ��� ���������
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;
	//����������� ������ ����
	class UStaticMesh* BlockStaticMesh = ConstructorHelpers::FObjectFinderOptional<UStaticMesh>(TEXT("StaticMesh'/Game/Cube.Cube'")).Get();
	BlockMesh = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(BlockStaticMesh);
	//�� ���� ���������� ��������
	tempMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("Material'/Game/RedMat.RedMat'")).Get();//����������� ��������
	BlockMesh->SetMaterial(0, tempMaterial);
	//���� ����������� � �������� �����
	BlockMesh->AttachTo(DummyRoot);
	// �� ����� ����� ������ ���� �����
	BlockMesh->OnClicked.AddDynamic(this, &AMyBox::BlockClicked);/*������� � UE 4.12, ��� ���������� ������� ������ ���� ��������� ���,
																 ����� ��������� �������������� �������� FKey.�������� OnClick / OnReleased
																 ������ ����� �������������� ��������, �����������, ����� ���� ��� ������������ �� �������*/
}

// ������� ��� ���������� ���� ����������
void AMyBox::LoadListMaterial() 
{
	tempMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("Material'/Game/TransperentMat.TransperentMat'")).Get();
	MyListMaterial.Add(tempMaterial);// ��������� �������� � ������ 

	tempMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("Material'/Game/BlueMat.BlueMat'")).Get();
	MyListMaterial.Add(tempMaterial);// ��������� �������� � ������ 

	tempMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("Material'/Game/RedMat.RedMat'")).Get();
	MyListMaterial.Add(tempMaterial);// ��������� �������� � ������ 

	tempMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("Material'/Game/WhiteMat.WhiteMat'")).Get();
	MyListMaterial.Add(tempMaterial);// ��������� �������� � ������ 

	tempMaterial = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("Material'/Game/YellowMat.YellowMat'")).Get();
	MyListMaterial.Add(tempMaterial);// ��������� �������� � ������ 
}

// ������� ��������� ���������� �����
void AMyBox::RandomColor()
{
	// �������� ������ ������� �� �����
	int32 ListMaterialLengh = MyListMaterial.Num() - 1;
	//������ ��������� ���� ����� �� 1 �� ������� ������� ����� -1
	IndexCurrentMaterial = FMath::RandRange(1, ListMaterialLengh);
}

// ������� ��� ������ ����� �� �����
void AMyBox::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonPressed)
{
	// ��� ������ �������� ����
	//RandomColor();
	OwnMap->SelectBlock(X, Y);
}

