// Fill out your copyright notice in the Description page of Project Settings.


#include "Kart.h"

// Sets default values
AKart::AKart():
AcceleratingForce(1000000.0),
RotatingForce(200.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	KartCollisionBox = CreateDefaultSubobject<UBoxComponent>("Kart Collision Box");
	KartMesh = CreateDefaultSubobject<UStaticMeshComponent>("Kart Mesh");
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	CenterOfMass = CreateDefaultSubobject<USceneComponent>("Center Of Mass");
	Suspension_FL = CreateDefaultSubobject<USuspension>("Suspension FL");
	Suspension_FR = CreateDefaultSubobject<USuspension>("Suspension FR");
	Suspension_RL = CreateDefaultSubobject<USuspension>("Suspension RL");
	Suspension_RR = CreateDefaultSubobject<USuspension>("Suspension RR");
	
	SetRootComponent(KartCollisionBox);
	KartMesh->SetupAttachment(KartCollisionBox);
	CameraBoom->SetupAttachment(RootComponent);
	Camera->SetupAttachment(CameraBoom);

	CenterOfMass->SetupAttachment(KartCollisionBox);
	
	Suspension_FL->SetupAttachment(KartCollisionBox);
	Suspension_FR->SetupAttachment(KartCollisionBox);
	Suspension_RL->SetupAttachment(KartCollisionBox);
	Suspension_RR->SetupAttachment(KartCollisionBox);

	KartCollisionBox->SetLinearDamping(3.0f);
	KartCollisionBox->SetAngularDamping(5.0f);
}

// Called when the game starts or when spawned
void AKart::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AKart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("Loc : %f"), GetVelocity().Y);
}

void AKart::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Accelerate" ,this, &AKart::Accelerate);
	PlayerInputComponent->BindAxis("Rotate" ,this, &AKart::RotateKart);
}

void AKart::Accelerate(float Value)
{
	if(Value>0)
	{
		KartCollisionBox->AddForceAtLocation(KartCollisionBox->GetForwardVector()*AcceleratingForce, CenterOfMass->GetComponentLocation());
	}
	if(Value<0)
	{
		KartCollisionBox->AddForceAtLocation(KartCollisionBox->GetForwardVector()*AcceleratingForce*FVector(-1, -1, 1),  CenterOfMass->GetComponentLocation());
	}
}

void AKart::RotateKart(float Value)
{
	if(Value!=0)
	{
		KartCollisionBox->AddTorqueInDegrees(FVector(0, 0, 1)*RotatingForce*Value, NAME_None, true);
	}
}
