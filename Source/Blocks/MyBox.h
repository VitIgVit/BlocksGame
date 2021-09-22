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

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) class USceneComponent* DummyRoot;//���������� ��� ����� ����

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) class UStaticMeshComponent* BlockMesh;//���������� ��� ����

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) class UMaterial* tempMaterial;//���������� ���������

	/* ������� �������� �����*/
	void CreateBlock();
	// ������� ���� ���������
	UPROPERTY() int32 IndexCurrentMaterial;
	//������ ������ ���������� ��� ������
	TArray<class UMaterial*> MyListMaterial;
	//������� ��� �������� ������ ����������
	void LoadListMaterial();
	//������� ���������� ������ ���������
	void RandomColor(); 
	// ������� ��� ������ ����� �� �����
	UFUNCTION()	void BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonPressed);

	// ���������� ��� �������� ������� ����� � ����� �����
	UPROPERTY() int32 X;   // ������� �� X
	UPROPERTY() int32 Y;  // ������� �� Y

	UPROPERTY() class AMyMap* OwnMap; // �����, ��� ������ ����
};
