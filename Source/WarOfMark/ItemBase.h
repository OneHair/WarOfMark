// Fill out your copyright notice in the Description page of Project Settings.
/*
SSW create & write
*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

class USphereComponent;
class APlayerCharacterBase;

class UBuffStateComponent;
enum class EItemKindsEnum : uint8;


UCLASS()
class WAROFMARK_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

	//被拾取时调用函数
	void BePicked(APlayerCharacterBase* player);

	//Bool: Can be Picked
	UPROPERTY(EditAnywhere, Category = "Attributes")
	bool bCanBePicked;
	//Bool: Can be droped
	UPROPERTY(EditAnywhere, Category = "Attributes")
	bool bCanBeDroped;


	//派生类的枚举类型
	//UPROPERTY(EditAnywhere, Category = "Attributes")
	EItemKindsEnum ItemKind;

	//Item carried BuffStateComponent
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	UBuffStateComponent* ItemBuffState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemName;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Static Mesh
	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	//Sphere Collision
	UPROPERTY(EditAnywhere, Category = "Components")
	USphereComponent* SphereComp;

	//All players nearly
	UPROPERTY(EditAnywhere, Category = "Attributes")
	TArray<APlayerCharacterBase*> NearlyPlayers;




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//当玩家接近
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	//当玩家离开
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
};
