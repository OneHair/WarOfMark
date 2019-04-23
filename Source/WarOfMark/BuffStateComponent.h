// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuffStateComponent.generated.h"

class APlayerCharacterBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WAROFMARK_API UBuffStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuffStateComponent();

	UPROPERTY(EditAnywhere, Category = "Attributes")
	int Hp;
	UPROPERTY(EditAnywhere, Category = "Attributes")
	int Armor;
	UPROPERTY(EditAnywhere, Category = "Attributes")
	float Vertigo;
	UPROPERTY(EditAnywhere, Category = "Attributes")
	float Silence;
	UPROPERTY(EditAnywhere, Category = "Attributes")
	float MoveSpeed;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
