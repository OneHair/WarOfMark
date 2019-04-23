// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterBase.h"
#include "Engine.h"
#include "ItemBase.h"
#include "BuffStateComponent.h"

// Sets default values
APlayerCharacterBase::APlayerCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//默认满背包为10
	FullBagNum = 10;

	InitHp = 100;
	InitArmor = 0;
	InitMoveSpeed = 50;

	//创建新的BuffState
	PlayerBuffState = CreateDefaultSubobject<UBuffStateComponent>(TEXT("CurrentBuffState"));


}

//可拾取物品栈添加
void APlayerCharacterBase::PickableItemsAdd(AItemBase* item)
{
	PickableItems.Add(item);
}

//可拾取物品栈减少
void APlayerCharacterBase::PickableItemsRemove(AItemBase * item)
{
	PickableItems.RemoveSingle(item);

}


//获得背包
TArray<AItemBase*> APlayerCharacterBase::GetBag()
{
	return Bag;
}


//查询背包是否已满
bool APlayerCharacterBase::IsBagFull()
{
	return Bag.Num() < FullBagNum ? false : true;
}

//按下拾取键尝试
void APlayerCharacterBase::TryPick()
{
	if (PickableItems.Num() > 0) {
		if (PickableItems.Last()->bCanBePicked && (!IsBagFull())) {
			PickSuccess();
		}
	}
}

//拾取成功
void APlayerCharacterBase::PickSuccess()
{
	Bag.Add(PickableItems.Last());

	PickableItems.Last()->BePicked(this);
	PickableItems.Pop();
}

void APlayerCharacterBase::StartJump()
{
	bPressedJump = true;
}

void APlayerCharacterBase::StopJump()
{
	bPressedJump = false;
}


UBuffStateComponent * APlayerCharacterBase::GetBuffState()
{
	if (PlayerBuffState) {
		return PlayerBuffState;
	}
	return nullptr;
}

// Called when the game starts or when spawned
void APlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine) {
		//FPlatformProcess::Sleep(1000);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("We are using PlayerCharacterBase!"));
		
	}

	//Init BuffState.
	if (GetBuffState()) {
		GetBuffState()->Hp = InitHp;
		GetBuffState()->Armor = InitArmor;
		GetBuffState()->MoveSpeed = InitMoveSpeed;
		GetBuffState()->Vertigo = 0;
		GetBuffState()->Silence = 0;
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

	//设置移动绑定
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacterBase::MoveRight);

	//设置旋转绑定
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacterBase::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacterBase::AddControllerPitchInput);

	//设置拾取绑定
	PlayerInputComponent->BindAction("Pick", IE_Pressed, this, &APlayerCharacterBase::TryPick);

	// 设置“动作”绑定。
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacterBase::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacterBase::StopJump);
}

void APlayerCharacterBase::MoveForward(float Value)
{
	// 明确哪个方向是“前进”，并记录玩家试图向此方向移动。
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	if (GetBuffState()) {
		Value *= (GetBuffState()->MoveSpeed) / 100;
	}
	AddMovementInput(Direction, Value);
}

void APlayerCharacterBase::MoveRight(float Value)
{
	// 明确哪个方向是“向右”，并记录玩家试图向此方向移动。
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	if (GetBuffState()) {
		Value *= (GetBuffState()->MoveSpeed) / 100;
	}
	AddMovementInput(Direction, Value);
}