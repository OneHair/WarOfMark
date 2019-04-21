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

	bCanBePicked = false;
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

void AItemBase::BePicked(APlayerCharacterBase* player)
{
	if (bCanBePicked && (!player->IsBagFull())) {
		player->PickSuccess();
		//what will happend when item be picked here!!!!!!!
	}
	else{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("This can't be picked now!"));
		}
	}
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
		if (! MyCharacter->IsBagFull()) {
			bCanBePicked = true;
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("I can be picked this now!"));
			}
			MyCharacter->PickableItemsAdd(this);
		}
	}
}

