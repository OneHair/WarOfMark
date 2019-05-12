// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacterBase.h"
#include "Character_Wizard.generated.h"

/**
 * 
 */

class AMagicBase;


UCLASS()
class WAROFMARK_API ACharacter_Wizard : public APlayerCharacterBase
{
	GENERATED_BODY()
	


public:
	//Generate magic from given three magic stocks
	AMagicBase* GenerateMagic(AMagicStock* stock1, AMagicStock* stock2, AMagicStock* stock3);




};
