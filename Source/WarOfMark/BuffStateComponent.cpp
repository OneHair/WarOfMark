// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffStateComponent.h"
#include "PlayerCharacterBase.h"
#include "Engine.h"

// Sets default values for this component's properties
UBuffStateComponent::UBuffStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UBuffStateComponent::BuffStateAdd(UBuffStateComponent* AnotherBuffState)
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Buff State Add!"));
	}
	//修正该BuffState组件所带的参数
	Hp += AnotherBuffState->Hp;
	Armor += AnotherBuffState->Armor;
	Vertigo += AnotherBuffState->Vertigo;
	Silence += AnotherBuffState->Silence;
	MoveSpeed += AnotherBuffState->MoveSpeed;
}

void UBuffStateComponent::BuffStateDec(UBuffStateComponent* AnotherBuffState)
{
	//修正该BuffState组件所带的参数
	Hp -= AnotherBuffState->Hp;
	Armor -= AnotherBuffState->Armor;
	Vertigo -= AnotherBuffState->Vertigo;
	Silence -= AnotherBuffState->Silence;
	MoveSpeed -= AnotherBuffState->MoveSpeed;
}

// Called when the game starts
void UBuffStateComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBuffStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

