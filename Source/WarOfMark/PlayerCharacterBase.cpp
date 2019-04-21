// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterBase.h"
#include "Engine.h"
#include "ItemBase.h"

// Sets default values
APlayerCharacterBase::APlayerCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BagNum = 0;
	FullBagNum = 10;
	PickableItemsNum = 0;
}

void APlayerCharacterBase::PickableItemsAdd(AItemBase* item)
{
	PickableItems.Add(item);
	PickableItemsNum++;
}

TArray<AItemBase*> APlayerCharacterBase::GetBag()
{
	return Bag;
}

int APlayerCharacterBase::GetBagNum()
{
	return BagNum;
}

bool APlayerCharacterBase::IsBagFull()
{
	return BagNum < FullBagNum ? false : true;
}

void APlayerCharacterBase::TryPick()
{
	if (PickableItemsNum > 0) {
		PickableItems[PickableItemsNum - 1]->BePicked(this);
	}
}

void APlayerCharacterBase::PickSuccess()
{
	Bag.Add(PickableItems[PickableItemsNum - 1]);
	BagNum++;
	PickableItems[PickableItemsNum - 1] = nullptr;
	PickableItemsNum--;
}

// Called when the game starts or when spawned
void APlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("We are using PlayerCharacterBase!"));
	}
}

// Called every frame
void APlayerCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// 调用后将功能绑定到输入
void APlayerCharacterBase::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 设置“移动”绑定。
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacterBase::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacterBase::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacterBase::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Pick", IE_Pressed, this, &APlayerCharacterBase::TryPick);
}

void APlayerCharacterBase::MoveForward(float Value)
{
	// 明确哪个方向是“前进”，并记录玩家试图向此方向移动。
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void APlayerCharacterBase::MoveRight(float Value)
{
	// 明确哪个方向是“向右”，并记录玩家试图向此方向移动。
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}