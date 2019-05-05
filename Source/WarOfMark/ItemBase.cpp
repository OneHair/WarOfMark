// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BuffStateComponent.h"
#include "PlayerCharacterBase.h"
#include "Enum/ItemKindsEnum.h"
#include "Engine.h"


// Sets default values
AItemBase::AItemBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bCanBePicked = true;
	bCanBeDroped = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetSimulatePhysics(true);
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetupAttachment(MeshComp);

	ItemKind = EItemKindsEnum::VE_MagicStock;

	//创建新的BuffState
	ItemBuffState = CreateDefaultSubobject<UBuffStateComponent>(TEXT("CurrentBuffState"));
}

UBuffStateComponent* AItemBase::GetBuffState()
{
	if (ItemBuffState) {
		return ItemBuffState;
	}
	return nullptr;
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	//Init BuffState.
	AddInstanceComponent(ItemBuffState);

	if (GetBuffState()) {
		GetBuffState()->Hp = 0;
		GetBuffState()->Armor = 0;
		GetBuffState()->MoveSpeed = 0;
		GetBuffState()->Vertigo = 0;
		GetBuffState()->Silence = 0;
	}
	
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Any Player begin overlap
void AItemBase::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (bCanBePicked) {
		APlayerCharacterBase* MyCharacter = Cast<APlayerCharacterBase>(OtherActor);
		if (MyCharacter) {
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("Someone nearly!"));
			}
			NearlyPlayers.Add(MyCharacter);
			MyCharacter->PickableItemsAdd(this);
		}
	}
}

//Any Player end overlap
void AItemBase::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if (bCanBePicked) {
		APlayerCharacterBase* MyCharacter = Cast<APlayerCharacterBase>(OtherActor);
		if (MyCharacter) {
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("Someone away!"));
			}
			MyCharacter->PickableItemsRemove(this);
			NearlyPlayers.RemoveSingle(MyCharacter);
		}
	}
}

void AItemBase::BePicked(APlayerCharacterBase* player)
{
	//what will happend when item be picked here!!!!!!!

	bCanBePicked = false;
	bCanBeDroped = true;

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("I'm be picked"));
	}
	Destroy();
}