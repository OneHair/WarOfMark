// Fill out your copyright notice in the Description page of Project Settings.

#include "WOM_Gamemode.h"
#include "Engine.h"
#include "PlayerCharacterBase.h"

void AWOM_Gamemode::StartPlay()
{
	Super::BeginPlay();

	Super::StartPlay();

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("WOM_Gamemode Begin!"));
	}
}
