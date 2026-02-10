// Copyright 13


#include "Actor/AuraFireBall.h"


AAuraFireBall::AAuraFireBall()
{
}

void AAuraFireBall::BeginPlay()
{
	Super::BeginPlay();
	
	StartOutgoingTimeline();
}

void AAuraFireBall::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
