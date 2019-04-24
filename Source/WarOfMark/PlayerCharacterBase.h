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

	//可拾取物品栈添加
	void PickableItemsAdd(AItemBase* item);
	//可拾取物品栈移除
	void PickableItemsRemove(AItemBase* item);

	TArray<AItemBase*> GetBag();

	//获取背包是否已满
	bool IsBagFull();

	//尝试拾取
	void TryPick();
	//拾取成功
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

	//可拾取物品栈
	UPROPERTY(EditAnywhere, Category = "Attributes")
	TArray<AItemBase*> PickableItems;

	//背包数组
	UPROPERTY(EditAnywhere, Category = "Attributes")
	TArray<AItemBase*> Bag;

	//背包满数量
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

	// 处理前后移动的输入。
	UFUNCTION()
	void MoveForward(float Value);

	// 处理左右移动的输入。
	UFUNCTION()
	void MoveRight(float Value);


	// 按下按键时设置跳跃标记。
	UFUNCTION()
		void StartJump();

	// 松开按键时清除跳跃标记。
	UFUNCTION()
		void StopJump();
};
