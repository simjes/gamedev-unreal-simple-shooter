// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);
		
		APawn* AIPawn = GetPawn();

		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), AIPawn->GetActorLocation());
	}
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	if (LineOfSightTo(PlayerPawn))
	{
		const FVector PlayerLocation = PlayerPawn->GetActorLocation();
		BlackboardComponent->SetValueAsVector(TEXT("PlayerLocation"), PlayerLocation);
		BlackboardComponent->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerLocation);
	}
	else
	{
		BlackboardComponent->ClearValue(TEXT("PlayerLocation"));
	}
}
