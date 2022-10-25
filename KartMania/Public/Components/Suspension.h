// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Suspension.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KARTMANIA_API USuspension : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USuspension();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	UPrimitiveComponent* BodyRef;

	FVector GetSuspensionVelocity();

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspension", meta = (AllowPrivateAccess = "true"))
	float SuspensionRayCastDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspension", meta = (AllowPrivateAccess = "true"))
	float SuspensionStrength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Suspension", meta = (AllowPrivateAccess = "true"))
	float SuspensionDamping;
	FVector PreviousLocation;
	float Compression;

	void SuspensionRayCast();
};
