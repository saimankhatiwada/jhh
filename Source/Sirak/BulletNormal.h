// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletNormal.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class SIRAK_API ABulletNormal : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ABulletNormal();
	

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* m_StaticMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ProjectileMovement")
	UProjectileMovementComponent* m_BuleteProjectileMovementComponent;


public:	
	
	virtual void Tick(float DeltaTime) override;

};
