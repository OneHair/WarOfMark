// Fill out your copyright notice in the Description page of Project Settings.


#include "Catalyst.h"
#include "Enum/ItemKindsEnum.h"
#include "BuffStateComponent.h"

ACatalyst::ACatalyst()
{
	//Initial default parameters:


	//Set the item kind
	ItemKind = EItemKindsEnum::VE_Catalyst;

	//test****************
	if (ItemBuffState) {
		ItemBuffState->Armor = 100;
	}
}
