// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "WeaponAK47.h"
#include "EngineUtils.h"

AMainPlayer::AMainPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;

	m_CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("m_CameraComp"));
	m_CameraComp->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale, "HeadSocket");
	m_CameraComp->bUsePawnControlRotation = true;

	m_PlayerHealth = 1.0f;
	m_PlayerArmor = 1.0f;
}


void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	if (m_PlayerMainWidgetClass != nullptr)
	{
		m_PlayerMainWidget = CreateWidget<UUserWidget>(GetWorld(), m_PlayerMainWidgetClass);
		if (m_PlayerMainWidget != nullptr)
		{
			m_PlayerMainWidget->AddToViewport();
		}
	}
	if (m_PlayerWeaponAK47Class != nullptr)
	{
		FActorSpawnParameters m_WeaponAK47Spawn;
		m_WeaponAK47Spawn.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AWeaponAK47* m_WeaponSpawn = GetWorld()->SpawnActor<AWeaponAK47>(m_PlayerWeaponAK47Class, m_WeaponAK47Spawn);
		m_WeaponSpawn->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "WeaponSocket");
	}
}

void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainPlayer::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMainPlayer::BeginCrouching);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMainPlayer::EndCrouching);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMainPlayer::BeginSprinting);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMainPlayer::EndSprinting);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMainPlayer::GunFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AMainPlayer::GunFireEnd);
	PlayerInputComponent->BindAction("DownSight", IE_Pressed, this, &AMainPlayer::IronSightBegin);

}


void AMainPlayer::MoveForward(float value)
{
	FRotator m_Rotation = Controller->GetControlRotation();
	FRotator m_YawRotation(0.0f, m_Rotation.Yaw, 0.0f);
	FVector m_Direction = FRotationMatrix(m_YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(m_Direction, value);
}

void AMainPlayer::MoveRight(float value)
{
	FRotator m_Rotation = Controller->GetControlRotation();
	FRotator m_YawRotation(0.0f, m_Rotation.Yaw, 0.0f);
	FVector m_Direction = FRotationMatrix(m_YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(m_Direction, value);
}

void AMainPlayer::BeginCrouching()
{
	m_IsCrouching = true;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	ACharacter::Crouch();
}

void AMainPlayer::EndCrouching()
{
	m_IsCrouching = false;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	ACharacter::UnCrouch();
}

void AMainPlayer::BeginSprinting()
{
	m_IsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
}

void AMainPlayer::EndSprinting()
{
	m_IsSprinting = false; 
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void AMainPlayer::TakeNormalDamage()
{
	m_PlayerArmor -= 0.15;
	if (m_PlayerArmor < 0.0f)
	{
		m_PlayerHealth = m_PlayerHealth + m_PlayerArmor;
		m_PlayerArmor = 0.0f;
		if (m_PlayerDamageWidgetClass != nullptr)
		{
			m_PlayerDamageWidget = CreateWidget(GetWorld(), m_PlayerDamageWidgetClass);
			if (m_PlayerDamageWidget != nullptr)
			{
				m_PlayerDamageWidget->AddToViewport();
			}
		}
	}
	else
	{
		if (m_PlayerDamageWidgetClass != nullptr)
		{
			m_PlayerDamageWidget = CreateWidget(GetWorld(), m_PlayerDamageWidgetClass);
			if (m_PlayerDamageWidget != nullptr)
			{
				m_PlayerDamageWidget->AddToViewport();
			}
		}
	}
}

void AMainPlayer::GunFire()
{
	for (TActorIterator<AWeaponAK47>  m_AKWeapon(GetWorld());  m_AKWeapon; ++m_AKWeapon)
	{
		m_AKWeapon->AutomaticFire();
	}
}

void AMainPlayer::GunFireEnd()
{
	for (TActorIterator<AWeaponAK47> m_AKWeapon(GetWorld()); m_AKWeapon; ++m_AKWeapon)
	{
		m_AKWeapon->AutomaticFireEnd();
	}
}

void AMainPlayer::IronSightBegin()
{

}
