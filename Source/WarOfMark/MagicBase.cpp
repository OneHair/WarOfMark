// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicBase.h"

// Sets default values
AMagicBase::AMagicBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMagicBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMagicBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

