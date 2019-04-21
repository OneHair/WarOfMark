// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacterBase.generated.h"


class AItemBase;

UCLASS()
class WAROFMARK_API APlayerCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacterBase();

	void PickableItemsAdd(AItemBase* item);
	TArray<AItemBase*> GetBag();
	int GetBagNum();
	bool IsBagFull();

	void TryPick();
	void PickSuccess();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<AItemBase*> PickableItems;
	UPROPERTY(BlueprintReadOnly, Category = "Attributes")
		int PickableItemsNum;
	UPROPERTY(EditAnywhere, Category = "Attributes")
	TArray<AItemBase*> Bag;
	UPROPERTY(EditAnywhere, Category = "Attributes")
		int BagNum;
	UPROPERTY(EditAnywhere, Category = "Attributes")
		int FullBagNum;

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

};
