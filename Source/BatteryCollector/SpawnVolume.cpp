// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Pickup.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Create the box component to represent spawn volume
	m_whereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("WhereToSpawn"));
	RootComponent = m_whereToSpawn;

	//Set the spawn delay range
	m_spawnDelayRangeLow = 1.f;
	m_spawnDelayRangeHigh = 4.5f;
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnVolume::GetRandomPointInVolume()
{
	FVector spawnOrigin = m_whereToSpawn->Bounds.Origin;
	FVector spawnExtent = m_whereToSpawn->Bounds.BoxExtent;

	return UKismetMathLibrary::RandomPointInBoundingBox(spawnOrigin, spawnExtent);
}

void ASpawnVolume::SetSpawningActive(bool bShouldSpawn)
{
	if (bShouldSpawn)
	{
		//Set timer on spawn pickup
		m_spawnDelay = FMath::FRandRange(m_spawnDelayRangeLow, m_spawnDelayRangeHigh);
		GetWorldTimerManager().SetTimer(m_spawnTimer, this, &ASpawnVolume::SpawnPickup, m_spawnDelay, false);
	}
	else
	{
		//Clear timer on spawn pickup
		GetWorldTimerManager().ClearTimer(m_spawnTimer);
	}
}

void ASpawnVolume::SpawnPickup()
{
	if (m_whatToSpawn)
	{
		UWorld* const world = GetWorld();
		if (world)
		{
			//Set spawn parameters
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			spawnParams.Instigator = Instigator;

			//Get random location to spawn at
			FVector spawnLocation = GetRandomPointInVolume();

			//Get a random rotation for the spawned item
			FRotator spawnRotation;
			spawnRotation.Yaw = FMath::FRand() * 360.f;
			spawnRotation.Pitch = FMath::FRand() * 360.f;
			spawnRotation.Roll = FMath::FRand() * 360.f;

			//Spawn the pickup
			APickup* const spawnedPickup = world->SpawnActor<APickup>(m_whatToSpawn, spawnLocation, spawnRotation, spawnParams);

			m_spawnDelay = FMath::FRandRange(m_spawnDelayRangeLow, m_spawnDelayRangeHigh);
			GetWorldTimerManager().SetTimer(m_spawnTimer, this, &ASpawnVolume::SpawnPickup, m_spawnDelay, false);
		}
	}
}