// Fill out your copyright notice in the Description page of Project Settings.
/*
SSW create & write
*/
#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacterBase.h"
#include "Character_Wizard.generated.h"



UCLASS()
class WAROFMARK_API ACharacter_Wizard : public APlayerCharacterBase
{
	GENERATED_BODY()
	


public:
	//Generate magic from given three magic stocks
	AMagicBase* GenerateMagic(AItemBase* MagicStock1, AItemBase* MagicStock2, AItemBase* MagicStock3);




};
