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

	//被拾取时调用函数
	void BePicked(APlayerCharacterBase* player);

	//可被拾取：在地上
	bool bCanBePicked;
	//可被丢弃：在背包中
	bool bCanBeDroped;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//SM
	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	//球形碰撞
	UPROPERTY(EditAnywhere, Category = "Components")
	USphereComponent* SphereComp;

	//临近的所有玩家
	UPROPERTY(EditAnywhere, Category = "Attribute")
	TArray<APlayerCharacterBase*> NearlyPlayers;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//当玩家接近
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	//当玩家离开
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
};
