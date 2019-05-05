// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicStock.h"
#include "Enum/ItemKindsEnum.h"

AMagicStock::AMagicStock() {
	//Initial default parameters:


	//Set the item kind
	ItemKind = EItemKindsEnum::VE_MagicStock;

	//Default type is element
	MagicStockType = EMagicStockEnum::VE_Element;

	MagicStockLevel = 1;

}