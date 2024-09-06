// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Barril.h"

// Sets default values
ABarril::ABarril()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		Barril(TEXT("StaticMesh'/Game/Geometry/BarrilMesh/BarriMeshStatic.BarriMeshStatic'"));
	
	//Mallas de la clase
	BarrilMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Malla_Barril"));
	BarrilMesh->SetStaticMesh(Barril.Object);
	BarrilMesh->SetRelativeScale3D(FVector(0.4, 0.4, 0.4));
	BarrilMesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	SetRootComponent(BarrilMesh);

	//Fisicas y colisiones
	BarrilMesh->SetSimulatePhysics(true);
	BarrilMesh->SetEnableGravity(true);
	BarrilCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Colision_Barril"));
	BarrilCollision->SetSphereRadius(225.0f);
	BarrilCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	BarrilCollision->SetupAttachment(GetRootComponent());

	RotationSpeed = 150.f;
}

// Called when the game starts or when spawned
void ABarril::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABarril::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Pitch += RotationSpeed * DeltaTime;

	if (CurrentRotation.Pitch > 360.0f)
	{
		CurrentRotation.Pitch -= 360.0f;
	}

	SetActorRotation(CurrentRotation);
}


