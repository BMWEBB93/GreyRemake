// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldWeatherSystem.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Kismet\GameplayStatics.h"

void UWorldWeatherSystem::Tick(float DeltaTime)
{
	


	if (Sun && Fog)
	{
		float SunPitch = Sun->GetComponentRotation().Pitch;

        float Normalized = FMath::Clamp((SunPitch + 90.f) / 180.f, 0.f, 1.f);

        float FogDensity = FMath::Lerp(MaxFogDensity, 0, Normalized);

        Fog->SetFogDensity(FogDensity);







		

		
	}

	

}

void UWorldWeatherSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Delay until world is loaded
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UWorldWeatherSystem::FindDaySequence);
}

void UWorldWeatherSystem::FindDaySequence()
{
    // Find the actor in the level (by class, since name may vary)
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);

    AActor* DaySequenceActor = nullptr;

    for (AActor* Actor : FoundActors)
    {
        if (Actor && Actor->GetName().Contains(TEXT("SunMoonDaySequenceActor")))
        {
            DaySequenceActor = Actor;
            break;
        }
    }

   
    if (DaySequenceActor)
    {
        // Get the directional light component
        TArray<UDirectionalLightComponent*> DirLights;
        DaySequenceActor->GetComponents<UDirectionalLightComponent>(DirLights);

        if (DirLights.Num() > 0)
        {
            Sun = DirLights[0]; // store pointer for Tick
        }

        TArray<UExponentialHeightFogComponent*> ExFogs;
        DaySequenceActor->GetComponents<UExponentialHeightFogComponent>(ExFogs);

        if (ExFogs.Num() > 0)
        {
            Fog = ExFogs[0];
        }
    }
    
}

TStatId UWorldWeatherSystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UWorldWeatherSystem, STATGROUP_Tickables);
}