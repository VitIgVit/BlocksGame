// Fill out your copyright notice in the Description page of Project Settings.
/*в версии 4.15 есть обновление, в которое необходимо включить большинство библиотек.
Я исправил ошибки, включив компоненты: #include "Components / StaticMeshComponent.h" 
и #include "Components / BoxComponent.h"*/
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"
#include "MyMap.h"
#include "MyBox.h"


//размер поля игрока
const int32 COL = 20, //количество блоков по вертикали
            ROW = 20; //количество блоков по горизонтали
                      // создание поля нужного размера
class AMyBox* Map[COL][ROW];

//Обьявляем структуру хранения координат проверяемой и удаляемых точек
struct MyPoint
{
	int32 XX, YY; //Координаты блока у которого будем проверять цвет

				//Конструктор структуры точки
	MyPoint() 
	{
		XX = 0; YY = 0;
	}
	//Переопределение оператора сравнения
	inline bool operator == (MyPoint a)
	{
		//Возвращаем результат сравнения полей
		return((a.XX == XX) && (a.YY == YY));
	}
};

// Список блоков на удаление
TArray<MyPoint> DeletePretindent; 

//Список точек на проверку
TArray<MyPoint> TestPointList(MyPoint coord)
{
	//Структура хранения и заноса в список подходящей точки
	MyPoint T;
	//Список точек, которые нужно проверить
	TArray<MyPoint> Result;

	//Расчитываем координаты точки справа
	T.XX = coord.XX - 1;    //Заполняем Х
	T.YY = coord.YY;        //Заполняем У
	                        //Проверяем левую сторону поля Х>=0
	if (T.XX >= 0) Result.Add(T);  //Добавляем точку в список

	//Расчитываем координаты точки слева
	T.XX = coord.XX + 1;    //Заполняем Х
	T.YY = coord.YY;        //Заполняем У
							//Проверяем правую Х < столбцов
	if (T.XX < COL) Result.Add(T);  //Добавляем точку в список

	//Расчитываем координаты точки сверху
	T.XX = coord.XX;    //Заполняем Х
	T.YY = coord.YY+1;        //Заполняем У
							//Проверяем правую сторону У < количества строк
	if (T.XX < ROW) Result.Add(T);  //Добавляем точку в список

	//Расчитываем координаты точки снизу
	T.XX = coord.XX;    //Заполняем Х
	T.YY = coord.YY - 1;        //Заполняем У
							//Проверяем левую сторону У >=0
	if (T.XX >= 0) Result.Add(T);  //Добавляем точку в список

	//Возвращаем результат
	return Result;
}

// функция вернет индекс найденого элемента
int32 SearchPoint(MyPoint P)
{
	//Перебираем все собранные в массиве блоки
	for (int s = 0; s < DeletePretindent.Num(); s++)
		//Если нашли такую же точку
		if (P == DeletePretindent[s])
			//Вернем номер точки
			return s;
	//Вернем -1 если не нашли точку
	return -1;
}

//Функция проверки блока
void TestBlock(int32 _X, int32 _Y, int32 IndexColor)
{
	MyPoint coord; //Собираем точку
	coord.XX = _X; //Задаем координату по Х
	coord.YY = _Y; //Задаем координату по У
	//Проверяем, есть ли такая точка в списке
	int32 Find = SearchPoint(coord);
	//Если не нашли,то есть смысл проверить точку
	if (Find == -1)
	{
		//Получим цвет точки
		int32 ColorIndex = Map[_X][_Y]->IndexCurrentMaterial;
		//Если цвет подходит, то будем что то делать
		if (IndexColor == ColorIndex)
		{
			//Добавляем претендента в список
			DeletePretindent.Add(coord);
			//Расчитываем соседние точки
			TArray<MyPoint> test = TestPointList(coord);
			//Получаем колличество найденых точек
			for (int TestPoint = 0; TestPoint < test.Num(); TestPoint++)
			{
				//Перебираем список точек с проверкой точек
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
	// создаем блок
	SpawnPoint = CreateDefaultSubobject<UBoxComponent>(TEXT("PointSpawnMyMap"));
	// указываю, что это будет корневая точка модели
	RootComponent = SpawnPoint;

	CreateMyscoreText();
}

// Called when the game starts or when spawned
void AMyMap::BeginPlay()
{
	Super::BeginPlay();
	//Создает поле при старте игры
	GenerateMap();
}

// Called every frame
void AMyMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Cдвигает блоки вниз во время обновления
	//MoveBlockDown();
}

// создаем поле игры во время старта игры
void AMyMap::GenerateMap()
{
	// координаты ширины и высоты блока
	float DZ = 110.05f,
		  DY = 57.05f;
	// получаем точку начала координат, сохраняем для восстановления в будущем
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
		// Двигаемся вверх по вертикали
		for (int32 yy = 0; yy < ROW; yy++)
		{
			for (int32 xx = 0; xx < COL; xx++)
			{
				// Создаем блок и сохраняем его в массив
				Map[xx][yy] = GetWorld()->SpawnActorAbsolute<AMyBox>(StartPoint, SpawnRotate);
				StartPoint.Y += DY;
				// Передаем блоку его статус
				Map[xx][yy]->X = xx; //Позиция по Х
				Map[xx][yy]->Y = yy; //Позиция по У
				Map[xx][yy]->OwnMap = this;

				//Расчитываем новую координату по вертикали
				StartPoint.Y += DY;
			}
			// Возвращаем блоки на начальную позицию
			StartPoint.Y = StartPointtmp.Y;
			//Создаем позицию по вертикали
			StartPoint.Z += DZ;
		}
	}
}

// Функция, которая будет получать координаты блока,на которую нажал игрок
void AMyMap::SelectBlock(int32 X, int32 Y)
{
	//Обнуляем блок из класса мар
	//Map[X][Y]->IndexCurrentMaterial = 0;

	//Обнуляем список претендентов
	DeletePretindent.Empty();

	//Получим цвет точки
	int32 ColorIndex = Map[X][Y]->IndexCurrentMaterial;

	//Запускаем поиск блоков
	TestBlock(X, Y, ColorIndex);

	//Если блоков больше 2х то удаляем их
	if (DeletePretindent.Num() > 2)
	{
		//Обнулим блоки
		for (int b = 0; b < DeletePretindent.Num(); b++)
		{
			//Обнуляем блок из класса Мар
			Map[DeletePretindent[b].XX][DeletePretindent[b].YY]->IndexCurrentMaterial = 0;
		}
		//В переменную подсчета очков прибавляем колличество уничтоженных блоков
		ScorePlayer += DeletePretindent.Num();
		//Обновляем текстовые поля
		MyScoreText->SetText(FText::AsNumber(ScorePlayer));
	}
	
	//Цикл проверяет есть ли пустые блоки и если есть, то обновляет цвет
	while (SearchZeroBlock())
	{
		MoveBlockDown();
	}

}

//Cдвигает блоки вниз во время обновления
void AMyMap::MoveBlockDown()
{
	//Перебираем все блоки поля
	for (int32 yy = 0; yy < ROW; yy++)
	{
		for (int32 xx = 0; xx < COL; xx++)
		{
			//Если есть пустой блок
			if (Map[xx][yy]->IndexCurrentMaterial == 0)
			{
				//Расчитываем новую точку
				int32 DY = yy + 1;
				//Проверяем,что над нами находится
				if (DY < ROW)
				{
					//Забираем цвет у верхнего блока
					Map[xx][yy]->IndexCurrentMaterial = Map[xx][DY]->IndexCurrentMaterial;
					//Забираем цвет у верхнего блока
					Map[xx][DY]->IndexCurrentMaterial = 0;
				}
				else
				{
					//Задаем блоку случайный цвет
					Map[xx][yy]->RandomColor();
				}
			}
		}
	}
}

//Функция проверки пустых блоков
bool AMyMap::SearchZeroBlock()
{
	//перебирает все блоки поля
	for (int32 yy = 0; yy < ROW; yy++)
	{
		for (int32 xx = 0; xx < COL; xx++)
		{
			//если есть пустой блок, то возвращает тру
			if (Map[xx][yy]->IndexCurrentMaterial == 0) return true;
		}
	}
	//Если нет пустых блоков возвращает ложь
	return false;
}

//Функция создания текста
void AMyMap::CreateMyscoreText()
{
	//Создаем объект текста
	MyScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText"));
	//Получам начальные координаты класса
	FVector StartPointtmp = SpawnPoint->Bounds.Origin;

	//Выравниваем текст по нужным координатам
	StartPointtmp.Z -= 300.f;
	StartPointtmp.Y -= 200.f;
	//Задаем угол повората текста к камере
	FRotator SpawnRotate = FRotator(0, -180, 0);
	MyScoreText->SetRelativeRotation(SpawnRotate);

	//Создаем координаты текста
	MyScoreText->SetRelativeLocation(StartPointtmp);
	//Устанавливаем размер теста
	MyScoreText->SetXScale(10.0f);
	MyScoreText->SetYScale(10.0f);
	//Привязываем текст к корневой точке класса
	MyScoreText->AttachTo(SpawnPoint);
	//Заполняем текс символом
	MyScoreText->SetText("000");
}

