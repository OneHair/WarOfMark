// Fill out your copyright notice in the Description page of Project Settings.
/*
SSW create & write
*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacterBase.generated.h"


class AItemBase;
class ACatalyst;
class AMagicStock;
class ATreasure;
class UBuffStateComponent;
class AMagicBase;
enum class EItemKindsEnum : uint8;
enum class EMagicStockEnum : uint8;


USTRUCT(BlueprintType)
struct FItemInBag
{
	GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere)
	EItemKindsEnum ItemType;

	//UPROPERTY(EditAnywhere)
	EMagicStockEnum MagicStockType;


	UPROPERTY(EditAnywhere)
	int MagicStockLevel;

	UPROPERTY(EditAnywhere)
	UBuffStateComponent* ItemBuffState;
		
};

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

	//Get Bag
	TArray<FItemInBag> GetBag();

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

	//Player carried BuffStateComponent
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	UBuffStateComponent* PlayerBuffState;


	//Virtual Function: Generate Magic
	virtual AMagicBase* GenerateMagic(AItemBase* MagicStock1, AItemBase* MagicStock2, AItemBase* MagicStock3);




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Can be picked items stack
	UPROPERTY(EditAnywhere, Category = "Attributes")
	TArray<AItemBase*> PickableItems;

	//Create bag (FItemInBag[])
	UPROPERTY(EditAnywhere, Category = "Attributes")
	TArray<FItemInBag> Bag;

	//The full bag number
	UPROPERTY(EditAnywhere, Category = "Attributes")
	int FullBagNum;

	

	TSubclassOf<ACatalyst> BPVAR_Catalyst;
	TSubclassOf<AMagicStock> BPVAR_MagicStock;
	TSubclassOf<ATreasure> BPVAR_Treasure;

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

	//Drop the last item in bag.
	UFUNCTION()
	void DropLastItem();
};
