// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletNormal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


ABulletNormal::ABulletNormal()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	
	m_StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_StaticMeshComp"));
	RootComponent = m_StaticMeshComp;

	m_BuleteProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("m_BuleteProjectileMovementComponent"));
	m_BuleteProjectileMovementComponent->InitialSpeed = 3500.0f;
	m_BuleteProjectileMovementComponent->MaxSpeed = 3500.0f;
	m_BuleteProjectileMovementComponent->ProjectileGravityScale = 0.01f;
}


void ABulletNormal::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABulletNormal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


