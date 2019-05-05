// Fill out your copyright notice in the Description page of Project Settings.


#include "Treasure.h"
#include "Enum/ItemKindsEnum.h"
#include "BuffStateComponent.h"

ATreasure::ATreasure()
{
	//Initial default parameters:


	//Set the item kind
	ItemKind = EItemKindsEnum::VE_Tresure;

	//test****************
	if (GetBuffState()) {
		GetBuffState()->MoveSpeed = 100;
	}
}
