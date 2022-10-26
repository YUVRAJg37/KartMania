// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/Suspension.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kart.generated.h"

UCLASS()
class KARTMANIA_API AKart : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKart();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	public:
	
	protected:

	
	private:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kart", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kart", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kart", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* KartCollisionBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kart", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* KartMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kart", meta = (AllowPrivateAccess = "true"))
	float AcceleratingForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kart", meta = (AllowPrivateAccess = "true"))
	float RotatingForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kart", meta = (AllowPrivateAccess = "true"))
	USceneComponent* CenterOfMass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kart", meta = (AllowPrivateAccess = "true"))
	USuspension* Suspension_FL;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kart", meta = (AllowPrivateAccess = "true"))
	USuspension* Suspension_FR;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kart", meta = (AllowPrivateAccess = "true"))
	USuspension* Suspension_RL;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kart", meta = (AllowPrivateAccess = "true"))
	USuspension* Suspension_RR;
	

	void Accelerate(float Value);
	void RotateKart(float Value);
};
