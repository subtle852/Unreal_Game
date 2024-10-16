// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_IsInAttackRange.h"
#include "Controller/GAIController.h"
#include "Character/GMonster.h"
#include "Character/GCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

const float UBTDecorator_IsInAttackRange::AttackRange(200.f);

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("IsInAttackRange");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	ensureMsgf(bResult != false, TEXT("Super::CalculateRawConditionValue() function has returned false"));

	AGAIController* AIController = Cast<AGAIController>(OwnerComp.GetAIOwner());
	ensureMsgf(IsValid(AIController), TEXT("Invalid AIController"));

	AGMonster* Monster = Cast<AGMonster>(AIController->GetPawn());
	ensureMsgf(IsValid(Monster), TEXT("Invalid Monster"));

	// 뒷걸음질 치는 경우는
	// AttackRange 안에 있다고 판단
	// 이렇게 해주지 않으면, 뒷걸음질을 AttackRange만큼 밖에 못가게 됨
	if(Monster->bIsNowMovingToBackFromTarget == true)
	{
		return true;
	}
	
	AGCharacter* TargetPlayerCharacter = Cast<AGCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AGAIController::TargetActorKey));
	if (IsValid(TargetPlayerCharacter) && TargetPlayerCharacter->IsPlayerControlled() == true)
	{
		return Monster->GetDistanceTo(TargetPlayerCharacter) <= AttackRange;
	}

	return false;
}
