// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Suspension.h"
	
USuspension::USuspension():
SuspensionRayCastDistance(100.0f),
SuspensionStrength(480000),
SuspensionDamping(10),
bIsInAir(false)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USuspension::BeginPlay()
{
	Super::BeginPlay();

	BodyRef = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
}

void USuspension::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(BodyRef)
	{
		SuspensionRayCast();
	}
}

void USuspension::SuspensionRayCast()
{
	FHitResult HitResult;
	
	GetWorld()->LineTraceSingleByChannel(HitResult, GetComponentLocation(),
		GetComponentLocation() + BodyRef->GetUpVector()*-1*SuspensionRayCastDistance, ECC_Visibility);

	if(HitResult.bBlockingHit)
	{
		bIsInAir = false;
		
		Compression = 1 - HitResult.Distance/SuspensionRayCastDistance;
		
		DrawDebugLine(GetWorld(), GetComponentLocation(), HitResult.ImpactPoint, FColor::Green);
		DrawDebugBox(GetWorld(), HitResult.ImpactPoint, FVector(5,5,5), FColor::Red);
		
		float SuspensionForce = SuspensionStrength*Compression - SuspensionDamping*GetSuspensionVelocity().Z;
		BodyRef->AddForceAtLocation(BodyRef->GetUpVector()*SuspensionForce, GetComponentLocation());
		DrawDebugString(GetWorld(), GetComponentLocation() , FString::Printf(TEXT("%.2f"), Compression), nullptr, FColor::White, 0, false, 2);
	}
	else
	{
		bIsInAir = true;
	}
}

FVector USuspension::GetSuspensionVelocity()
{
	FVector CurrentLocation = GetComponentLocation();
	FVector Velocity = (PreviousLocation - CurrentLocation) /GetWorld()->GetDeltaSeconds();
	PreviousLocation = CurrentLocation;
	
	return Velocity;
}

