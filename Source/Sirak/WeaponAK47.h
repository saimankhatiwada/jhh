// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponAK47.generated.h"

class USkeletalMeshComponent;
class ABulletNormal;
class UCameraComponent;


UCLASS()
class SIRAK_API AWeaponAK47 : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AWeaponAK47();

	void AutomaticFire();
	void AutomaticFireEnd();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	USkeletalMeshComponent* m_SkeletalMeshComp;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	UCameraComponent* m_IronSightCameraComp;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet")
	TSubclassOf<ABulletNormal> m_BulletNormalClass;

	FTimerHandle m_FiringTimer;

	void Fire();
public:	
	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet")
	int m_Ammo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet")
	float m_FireRate;
};
