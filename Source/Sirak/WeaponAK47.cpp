// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponAK47.h"
#include "Components/SkeletalMeshComponent.h"
#include "BulletNormal.h"
#include "Engine/Engine.h"
#include "Camera/CameraComponent.h"



AWeaponAK47::AWeaponAK47()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	m_SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("m_SkeletalMeshComp"));
	RootComponent = m_SkeletalMeshComp;


	m_Ammo = 45;
	m_FireRate = 0.1f;

}


void AWeaponAK47::BeginPlay()
{
	Super::BeginPlay();
	
}


void AWeaponAK47::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponAK47::Fire()
{
	if (m_BulletNormalClass != nullptr)
	{
		m_Ammo = m_Ammo - 1;
		if (m_Ammo!=NULL && m_Ammo >= 1)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::SanitizeFloat(m_Ammo));
			FVector BulletSpawnLocation = m_SkeletalMeshComp->GetSocketLocation("BulletSocket");
			FRotator BulletSpawnRotation = m_SkeletalMeshComp->GetSocketRotation("BulletSocket");

			FActorSpawnParameters m_BulletNormalSpawn;
			m_BulletNormalSpawn.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			ABulletNormal* m_Bullet = GetWorld()->SpawnActor<ABulletNormal>(m_BulletNormalClass, BulletSpawnLocation, BulletSpawnRotation, m_BulletNormalSpawn);

		}
	}
	
}

void AWeaponAK47::AutomaticFire()
{
		GetWorld()->GetTimerManager().SetTimer(m_FiringTimer, this, &AWeaponAK47::Fire, m_FireRate, true);
}

void AWeaponAK47::AutomaticFireEnd()
{
	GetWorld()->GetTimerManager().ClearTimer(m_FiringTimer);
}
