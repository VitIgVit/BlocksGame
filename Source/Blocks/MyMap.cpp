// Fill out your copyright notice in the Description page of Project Settings.
/*� ������ 4.15 ���� ����������, � ������� ���������� �������� ����������� ���������.
� �������� ������, ������� ����������: #include "Components / StaticMeshComponent.h" 
� #include "Components / BoxComponent.h"*/
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"
#include "MyMap.h"
#include "MyBox.h"


//������ ���� ������
const int32 COL = 20, //���������� ������ �� ���������
            ROW = 20; //���������� ������ �� �����������
                      // �������� ���� ������� �������
class AMyBox* Map[COL][ROW];

//��������� ��������� �������� ��������� ����������� � ��������� �����
struct MyPoint
{
	int32 XX, YY; //���������� ����� � �������� ����� ��������� ����

				//����������� ��������� �����
	MyPoint() 
	{
		XX = 0; YY = 0;
	}
	//��������������� ��������� ���������
	inline bool operator == (MyPoint a)
	{
		//���������� ��������� ��������� �����
		return((a.XX == XX) && (a.YY == YY));
	}
};

// ������ ������ �� ��������
TArray<MyPoint> DeletePretindent; 

//������ ����� �� ��������
TArray<MyPoint> TestPointList(MyPoint coord)
{
	//��������� �������� � ������ � ������ ���������� �����
	MyPoint T;
	//������ �����, ������� ����� ���������
	TArray<MyPoint> Result;

	//����������� ���������� ����� ������
	T.XX = coord.XX - 1;    //��������� �
	T.YY = coord.YY;        //��������� �
	                        //��������� ����� ������� ���� �>=0
	if (T.XX >= 0) Result.Add(T);  //��������� ����� � ������

	//����������� ���������� ����� �����
	T.XX = coord.XX + 1;    //��������� �
	T.YY = coord.YY;        //��������� �
							//��������� ������ � < ��������
	if (T.XX < COL) Result.Add(T);  //��������� ����� � ������

	//����������� ���������� ����� ������
	T.XX = coord.XX;    //��������� �
	T.YY = coord.YY+1;        //��������� �
							//��������� ������ ������� � < ���������� �����
	if (T.XX < ROW) Result.Add(T);  //��������� ����� � ������

	//����������� ���������� ����� �����
	T.XX = coord.XX;    //��������� �
	T.YY = coord.YY - 1;        //��������� �
							//��������� ����� ������� � >=0
	if (T.XX >= 0) Result.Add(T);  //��������� ����� � ������

	//���������� ���������
	return Result;
}

// ������� ������ ������ ��������� ��������
int32 SearchPoint(MyPoint P)
{
	//���������� ��� ��������� � ������� �����
	for (int s = 0; s < DeletePretindent.Num(); s++)
		//���� ����� ����� �� �����
		if (P == DeletePretindent[s])
			//������ ����� �����
			return s;
	//������ -1 ���� �� ����� �����
	return -1;
}

//������� �������� �����
void TestBlock(int32 _X, int32 _Y, int32 IndexColor)
{
	MyPoint coord; //�������� �����
	coord.XX = _X; //������ ���������� �� �
	coord.YY = _Y; //������ ���������� �� �
	//���������, ���� �� ����� ����� � ������
	int32 Find = SearchPoint(coord);
	//���� �� �����,�� ���� ����� ��������� �����
	if (Find == -1)
	{
		//������� ���� �����
		int32 ColorIndex = Map[_X][_Y]->IndexCurrentMaterial;
		//���� ���� ��������, �� ����� ��� �� ������
		if (IndexColor == ColorIndex)
		{
			//��������� ����������� � ������
			DeletePretindent.Add(coord);
			//����������� �������� �����
			TArray<MyPoint> test = TestPointList(coord);
			//�������� ����������� �������� �����
			for (int TestPoint = 0; TestPoint < test.Num(); TestPoint++)
			{
				//���������� ������ ����� � ��������� �����
				TestBlock(test[TestPoint].XX, test[TestPoint].YY, IndexColor);
			}
		}
	}
}

// Sets default values
AMyMap::AMyMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// ������� ����
	SpawnPoint = CreateDefaultSubobject<UBoxComponent>(TEXT("PointSpawnMyMap"));
	// ��������, ��� ��� ����� �������� ����� ������
	RootComponent = SpawnPoint;

	CreateMyscoreText();
}

// Called when the game starts or when spawned
void AMyMap::BeginPlay()
{
	Super::BeginPlay();
	//������� ���� ��� ������ ����
	GenerateMap();
}

// Called every frame
void AMyMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//C������� ����� ���� �� ����� ����������
	//MoveBlockDown();
}

// ������� ���� ���� �� ����� ������ ����
void AMyMap::GenerateMap()
{
	// ���������� ������ � ������ �����
	float DZ = 110.05f,
		  DY = 57.05f;
	// �������� ����� ������ ���������, ��������� ��� �������������� � �������
	FVector StartPointtmp = SpawnPoint->Bounds.Origin;
	//
	FVector StartPoint = SpawnPoint->Bounds.Origin;
	FRotator SpawnRotate = FRotator(0, 0, 0);

	FActorSpawnParameters SpawnParam;
	SpawnParam.Owner = this;
	//SpawnParam.Instigator = this;

	class UWorld* W = GetWorld();
	if (W)
	{
		// ��������� ����� �� ���������
		for (int32 yy = 0; yy < ROW; yy++)
		{
			for (int32 xx = 0; xx < COL; xx++)
			{
				// ������� ���� � ��������� ��� � ������
				Map[xx][yy] = GetWorld()->SpawnActorAbsolute<AMyBox>(StartPoint, SpawnRotate);
				StartPoint.Y += DY;
				// �������� ����� ��� ������
				Map[xx][yy]->X = xx; //������� �� �
				Map[xx][yy]->Y = yy; //������� �� �
				Map[xx][yy]->OwnMap = this;

				//����������� ����� ���������� �� ���������
				StartPoint.Y += DY;
			}
			// ���������� ����� �� ��������� �������
			StartPoint.Y = StartPointtmp.Y;
			//������� ������� �� ���������
			StartPoint.Z += DZ;
		}
	}
}

// �������, ������� ����� �������� ���������� �����,�� ������� ����� �����
void AMyMap::SelectBlock(int32 X, int32 Y)
{
	//�������� ���� �� ������ ���
	//Map[X][Y]->IndexCurrentMaterial = 0;

	//�������� ������ ������������
	DeletePretindent.Empty();

	//������� ���� �����
	int32 ColorIndex = Map[X][Y]->IndexCurrentMaterial;

	//��������� ����� ������
	TestBlock(X, Y, ColorIndex);

	//���� ������ ������ 2� �� ������� ��
	if (DeletePretindent.Num() > 2)
	{
		//������� �����
		for (int b = 0; b < DeletePretindent.Num(); b++)
		{
			//�������� ���� �� ������ ���
			Map[DeletePretindent[b].XX][DeletePretindent[b].YY]->IndexCurrentMaterial = 0;
		}
		//� ���������� �������� ����� ���������� ����������� ������������ ������
		ScorePlayer += DeletePretindent.Num();
		//��������� ��������� ����
		MyScoreText->SetText(FText::AsNumber(ScorePlayer));
	}
	
	//���� ��������� ���� �� ������ ����� � ���� ����, �� ��������� ����
	while (SearchZeroBlock())
	{
		MoveBlockDown();
	}

}

//C������� ����� ���� �� ����� ����������
void AMyMap::MoveBlockDown()
{
	//���������� ��� ����� ����
	for (int32 yy = 0; yy < ROW; yy++)
	{
		for (int32 xx = 0; xx < COL; xx++)
		{
			//���� ���� ������ ����
			if (Map[xx][yy]->IndexCurrentMaterial == 0)
			{
				//����������� ����� �����
				int32 DY = yy + 1;
				//���������,��� ��� ���� ���������
				if (DY < ROW)
				{
					//�������� ���� � �������� �����
					Map[xx][yy]->IndexCurrentMaterial = Map[xx][DY]->IndexCurrentMaterial;
					//�������� ���� � �������� �����
					Map[xx][DY]->IndexCurrentMaterial = 0;
				}
				else
				{
					//������ ����� ��������� ����
					Map[xx][yy]->RandomColor();
				}
			}
		}
	}
}

//������� �������� ������ ������
bool AMyMap::SearchZeroBlock()
{
	//���������� ��� ����� ����
	for (int32 yy = 0; yy < ROW; yy++)
	{
		for (int32 xx = 0; xx < COL; xx++)
		{
			//���� ���� ������ ����, �� ���������� ���
			if (Map[xx][yy]->IndexCurrentMaterial == 0) return true;
		}
	}
	//���� ��� ������ ������ ���������� ����
	return false;
}

//������� �������� ������
void AMyMap::CreateMyscoreText()
{
	//������� ������ ������
	MyScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText"));
	//������� ��������� ���������� ������
	FVector StartPointtmp = SpawnPoint->Bounds.Origin;

	//����������� ����� �� ������ �����������
	StartPointtmp.Z -= 300.f;
	StartPointtmp.Y -= 200.f;
	//������ ���� �������� ������ � ������
	FRotator SpawnRotate = FRotator(0, -180, 0);
	MyScoreText->SetRelativeRotation(SpawnRotate);

	//������� ���������� ������
	MyScoreText->SetRelativeLocation(StartPointtmp);
	//������������� ������ �����
	MyScoreText->SetXScale(10.0f);
	MyScoreText->SetYScale(10.0f);
	//����������� ����� � �������� ����� ������
	MyScoreText->AttachTo(SpawnPoint);
	//��������� ���� ��������
	MyScoreText->SetText("000");
}

