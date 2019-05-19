// Fill out your copyright notice in the Description page of Project Settings.
/*
SSW create & write
*/
#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "MagicStock.generated.h"


UENUM(BlueprintType)
enum class EMagicStockEnum : uint8
{
	VE_Element UMETA(DisplayName = "Element"),
	VE_Plasticity UMETA(DisplayName = "Plasticity"),
	VE_Effection UMETA(DisplayName = "Effection")
};


UCLASS()
class WAROFMARK_API AMagicStock : public AItemBase
{
	GENERATED_BODY()

public:
	AMagicStock();
	//MagicStockType created
	UPROPERTY(EditAnywhere, Category = "MagicStockAttributes")
	EMagicStockEnum MagicStockType;

	//MagicStockLevel created
	UPROPERTY(EditAnywhere, Category = "MagicStockAttributes")
	int MagicStockLevel;


protected:

	
	
};
