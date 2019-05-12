// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerCharacterBase.h"
#include "Engine.h"
#include "ItemBase.h"
#include "Items/MagicStock.h"
#include "Items/Treasure.h"
#include "Items/Catalyst.h"
#include "BuffStateComponent.h"
#include "Enum/ItemKindsEnum.h"
#include "Items/MagicStock.h"

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


	
	static ConstructorHelpers::FObjectFinder<UBlueprint> BP_CatalystTemp(TEXT("Blueprint'/Game/Blueprint/Environment/Items/BP_Catalyst.BP_Catalyst'"));
	if (BP_CatalystTemp.Object)
	{
		BPVAR_Catalyst = (UClass*)BP_CatalystTemp.Object->GeneratedClass;
	}
	static ConstructorHelpers::FObjectFinder<UBlueprint> BP_TreasureTemp(TEXT("Blueprint'/Game/Blueprint/Environment/Items/BP_Treasure.BP_Treasure'"));
	if (BP_TreasureTemp.Object)
	{
		BPVAR_Treasure = (UClass*)BP_TreasureTemp.Object->GeneratedClass;
	}
	static ConstructorHelpers::FObjectFinder<UBlueprint> BP_MagicStockTemp(TEXT("Blueprint'/Game/Blueprint/Environment/Items/BP_MagicStock.BP_MagicStock'"));
	if (BP_MagicStockTemp.Object)
	{
		BPVAR_MagicStock = (UClass*)BP_MagicStockTemp.Object->GeneratedClass;
	}
	
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
TArray<FItemInBag> APlayerCharacterBase::GetBag()
{
	return Bag;
}


//查询背包是否已满
bool APlayerCharacterBase::IsBagFull()
{
	return Bag.Num() < FullBagNum ? false : true;
}

//-------------------------Pick------------------------------
//Try to pick item
void APlayerCharacterBase::TryPick()
{
	if (PickableItems.Num() > 0) {
		//Is bag full? & item can be picked
		if (PickableItems.Last()->bCanBePicked && (!IsBagFull())) {
			PickSuccess();
		}
	}
}

//Pick Successful
void APlayerCharacterBase::PickSuccess()
{
	FItemInBag NewItem;
	NewItem.ItemBuffState = PickableItems.Last()->GetBuffState();
	NewItem.ItemType = PickableItems.Last()->ItemKind;

	//判断捡起的物品的种类
	if (PickableItems.Last()->ItemKind == EItemKindsEnum::VE_MagicStock) {

		AMagicStock* CurrentStock = Cast<AMagicStock>(PickableItems.Last());
		if (CurrentStock) {
			NewItem.MagicStockLevel = CurrentStock->MagicStockLevel;
			NewItem.MagicStockType = CurrentStock->MagicStockType;
		}
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("I pick a magic stock!"));
			NewItem.MagicStockLevel = 0;
		}
	}
	else if (PickableItems.Last()->ItemKind == EItemKindsEnum::VE_Tresure) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("I pick a treasure!"));
			NewItem.MagicStockLevel = 0;
		}
	}
	else if (PickableItems.Last()->ItemKind == EItemKindsEnum::VE_Catalyst) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("I pick a Catalyst!"));

		}
	}

	Bag.Add(NewItem);

	PickableItems.Pop()->BePicked(this);
}
//-----------------------------------------------------------

void APlayerCharacterBase::StartJump()
{
	bPressedJump = true;
}

void APlayerCharacterBase::StopJump()
{
	bPressedJump = false;
}


void APlayerCharacterBase::DropLastItem()
{
	if (Bag.Num() > 0) {
		FItemInBag NewItem = Bag.Pop();
		if (NewItem.ItemType == EItemKindsEnum::VE_MagicStock) {
			GetWorld()->SpawnActor<AMagicStock>(BPVAR_MagicStock, GetActorLocation(), GetActorRotation());
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("I drop a MagicStock!"));
				NewItem.MagicStockLevel = 0;
			}
		}
		else if (NewItem.ItemType == EItemKindsEnum::VE_Tresure) {
			GetWorld()->SpawnActor<ATreasure>(BPVAR_Treasure, GetActorLocation(), GetActorRotation());
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("I drop a Treasure!"));
				NewItem.MagicStockLevel = 0;
			}
		}
		else if (NewItem.ItemType == EItemKindsEnum::VE_Catalyst) {
			GetWorld()->SpawnActor<ACatalyst>(BPVAR_Catalyst, GetActorLocation(), GetActorRotation());
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("I drop a BP_Catalyst!"));

			}
		}
	}
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
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("We are using PlayerCharacterBase!"));
		
	}

	//Init BuffState.
	AddInstanceComponent(PlayerBuffState);

	if (GetBuffState()) {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Playerbuffstate exist."));

		}
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


//Bind the input function
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

	//设置跳跃绑定
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacterBase::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacterBase::StopJump);

	//Drop Binding
	PlayerInputComponent->BindAction("Drop", IE_Pressed, this, &APlayerCharacterBase::DropLastItem);
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