// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//All pickups start active
	m_bIsActive = true;

	//Create static mesh component
	m_pickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = m_pickupMesh;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Returns active state
bool APickup::IsActive() const
{
	return m_bIsActive;
}

//Changes active state
void APickup::SetActive(bool NewPickupState)
{
	m_bIsActive = NewPickupState;
}

void APickup::WasCollected_Implementation()
{
	//Log a debug message
	FString pickupDebugString = GetName();
	UE_LOG(LogClass, Log, TEXT("You have collected %s"), *pickupDebugString);
}