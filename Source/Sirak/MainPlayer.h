// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainPlayer.generated.h"

class UCameraComponent;
class UUserWidget;
class AWeaponAK47;

UCLASS()
class SIRAK_API AMainPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainPlayer();

	UFUNCTION(BlueprintPure, Category = "Player_Essentials")
	float GetPlayerHealth() { return m_PlayerHealth; }

	UFUNCTION(BlueprintPure, Category = "Player_Essentials")
	float GetPlayerArmor() { return m_PlayerArmor; }

	UFUNCTION(BlueprintPure, Category = "Animation_Essentials")
	bool GetPlayerCrouchingState() { return  m_IsCrouching; }

	UFUNCTION(BlueprintPure, Category = "Animation_Essentials")
	bool GetPlayerSprintingState() { return m_IsSprinting; }

	UFUNCTION(BlueprintCallable, Category = "Damage")
	void TakeNormalDamage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* m_CameraComp;

	UPROPERTY(BlueprintReadOnly, Category = "PlayerHUD")
	UUserWidget* m_PlayerMainWidget;

	UPROPERTY(BlueprintReadOnly, Category = "PlayerHUD")
	UUserWidget* m_PlayerDamageWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerHUD")
	TSubclassOf<UUserWidget> m_PlayerMainWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerHUD")
	TSubclassOf<UUserWidget> m_PlayerDamageWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AWeaponAK47> m_PlayerWeaponAK47Class;

	void MoveForward(float value);
	void MoveRight(float value);
	void BeginCrouching();
	void EndCrouching();
	void BeginSprinting();
	void EndSprinting();

	void GunFire();
	void GunFireEnd();

	void IronSightBegin();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Player_Essentials")
	float m_PlayerHealth;

	UPROPERTY(VisibleAnywhere, Category = "Player_Essentials")
	float m_PlayerArmor;

	bool m_IsCrouching;
	bool m_IsSprinting;
};
