// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacterBase.generated.h"


class AItemBase;
class UBuffStateComponent;

UCLASS()
class WAROFMARK_API APlayerCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacterBase();

	//��ʰȡ��Ʒջ���
	void PickableItemsAdd(AItemBase* item);
	//��ʰȡ��Ʒջ�Ƴ�
	void PickableItemsRemove(AItemBase* item);

	TArray<AItemBase*> GetBag();

	//��ȡ�����Ƿ�����
	bool IsBagFull();

	//����ʰȡ
	void TryPick();
	//ʰȡ�ɹ�
	void PickSuccess();

	//Init Hp
	UPROPERTY(EditAnywhere, Category = "Attributes")
	int InitHp;

	//Init Armor
	UPROPERTY(EditAnywhere, Category = "Attributes")
	int InitArmor;

	//Init Move Speed
	UPROPERTY(EditAnywhere, Category = "Attributes")
	int InitMoveSpeed;

	UBuffStateComponent* GetBuffState();

	



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//��ʰȡ��Ʒջ
	UPROPERTY(EditAnywhere, Category = "Attributes")
	TArray<AItemBase*> PickableItems;

	//��������
	UPROPERTY(EditAnywhere, Category = "Attributes")
	TArray<AItemBase*> Bag;

	//����������
	UPROPERTY(EditAnywhere, Category = "Attributes")
	int FullBagNum;

	//Player carried BuffStateComponent
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	UBuffStateComponent* PlayerBuffState;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ����ǰ���ƶ������롣
	UFUNCTION()
	void MoveForward(float Value);

	// ���������ƶ������롣
	UFUNCTION()
	void MoveRight(float Value);


	// ���°���ʱ������Ծ��ǡ�
	UFUNCTION()
		void StartJump();

	// �ɿ�����ʱ�����Ծ��ǡ�
	UFUNCTION()
		void StopJump();
};
