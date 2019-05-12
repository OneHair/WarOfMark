// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemKindsEnum.generated.h"

UENUM(BlueprintType)
enum class EItemKindsEnum : uint8
{
	VE_MagicStock UMETA(DisplayName = "MagicStock"),
	VE_Tresure UMETA(DisplayName = "Treasure"),
	VE_Catalyst UMETA(DisplayName = "Catalyst")
};
