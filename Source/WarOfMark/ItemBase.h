// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

class USphereComponent;
class APlayerCharacterBase;
UCLASS()
class WAROFMARK_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

	void BePicked(APlayerCharacterBase* player);

	//Booleans to control pick/drop.
	bool bCanBePicked;
	bool bCanBeDroped;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Static Mesh pre-Called, can be edited in BP.
	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	//Sphere Collison pre-Called, can be edited in BP.
	UPROPERTY(EditAnywhere, Category = "Components")
	USphereComponent* SphereComp;

	//Player Begin Move Nearly from this item.
	void PlayerBeginOverlap();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
