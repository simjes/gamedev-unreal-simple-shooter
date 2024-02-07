// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"

#include "AIController.h"
#include "ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = "Shoot";
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBTTaskNode::ExecuteTask(OwnerComp, NodeMemory);

	const AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	AShooterCharacter* Pawn = Cast<AShooterCharacter>(AIController->GetPawn());
	if (!Pawn)
	{
		return EBTNodeResult::Failed;
	}

	Pawn->Fire();
	return EBTNodeResult::Succeeded;
}
