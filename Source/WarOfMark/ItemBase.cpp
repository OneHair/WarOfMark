// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerCharacterBase.h"
#include "Engine.h"

class USphereComponent;

// Sets default values
AItemBase::AItemBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bCanBePicked = true;
	bCanBeDroped = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBase::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	APlayerCharacterBase* MyCharacter = Cast<APlayerCharacterBase>(OtherActor);
	if (MyCharacter) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Someone nearly!"));
		}
		NearlyPlayers.Add(MyCharacter);
		MyCharacter->PickableItemsAdd(this);
	}
}

void AItemBase::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	APlayerCharacterBase* MyCharacter = Cast<APlayerCharacterBase>(OtherActor);
	if (MyCharacter) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Someone away!"));
		}
		MyCharacter->PickableItemsRemove(this);
		NearlyPlayers.RemoveSingle(MyCharacter);
	}

}

void AItemBase::BePicked(APlayerCharacterBase* player)
{
	//what will happend when item be picked here!!!!!!!

	bCanBePicked = false;
	bCanBeDroped = true;

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("I'm be picked"));
	}
}