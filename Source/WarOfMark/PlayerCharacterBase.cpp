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

	//Ĭ��������Ϊ10
	FullBagNum = 10;

	InitHp = 100;
	InitArmor = 0;
	InitMoveSpeed = 50;

	//�����µ�BuffState
	PlayerBuffState = CreateDefaultSubobject<UBuffStateComponent>(TEXT("CurrentBuffState"));


}

//��ʰȡ��Ʒջ���
void APlayerCharacterBase::PickableItemsAdd(AItemBase* item)
{
	PickableItems.Add(item);
}

//��ʰȡ��Ʒջ����
void APlayerCharacterBase::PickableItemsRemove(AItemBase * item)
{
	PickableItems.RemoveSingle(item);

}


//��ñ���
TArray<AItemBase*> APlayerCharacterBase::GetBag()
{
	return Bag;
}


//��ѯ�����Ƿ�����
bool APlayerCharacterBase::IsBagFull()
{
	return Bag.Num() < FullBagNum ? false : true;
}

//����ʰȡ������
void APlayerCharacterBase::TryPick()
{
	if (PickableItems.Num() > 0) {
		if (PickableItems.Last()->bCanBePicked && (!IsBagFull())) {
			PickSuccess();
		}
	}
}

//ʰȡ�ɹ�
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


// ���ú󽫹��ܰ󶨵�����
void APlayerCharacterBase::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//�����ƶ���
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacterBase::MoveRight);

	//������ת��
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacterBase::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacterBase::AddControllerPitchInput);

	//����ʰȡ��
	PlayerInputComponent->BindAction("Pick", IE_Pressed, this, &APlayerCharacterBase::TryPick);

	// ���á��������󶨡�
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacterBase::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacterBase::StopJump);
}

void APlayerCharacterBase::MoveForward(float Value)
{
	// ��ȷ�ĸ������ǡ�ǰ����������¼�����ͼ��˷����ƶ���
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	if (GetBuffState()) {
		Value *= (GetBuffState()->MoveSpeed) / 100;
	}
	AddMovementInput(Direction, Value);
}

void APlayerCharacterBase::MoveRight(float Value)
{
	// ��ȷ�ĸ������ǡ����ҡ�������¼�����ͼ��˷����ƶ���
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	if (GetBuffState()) {
		Value *= (GetBuffState()->MoveSpeed) / 100;
	}
	AddMovementInput(Direction, Value);
}