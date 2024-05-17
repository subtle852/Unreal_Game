// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GAnimInstance.generated.h"

/**
 * 
 */

class UAnimMontage;

UENUM(BlueprintType)
enum class ELocomotionState : uint8
{
	None,
	Idle,
	Walk,
	End
};

UENUM(BlueprintType)
enum class EMovementDirection : uint8
{
	None,
	Fwd,
	Bwd,
	Left,
	Right,
	End
};

UCLASS()
class GAMEPROJECT_API UGAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UGAnimInstance();

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	ELocomotionState GetLocomotionState() const { return LocomotionState; }

	EMovementDirection GetMovementDirection() const { return MovementDirection; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAnimInstance", meta = (AllowPrivateAccess))
	FVector Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAnimInstance", meta = (AllowPrivateAccess))
	float CurrentSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAnimInstance", meta = (AllowPrivateAccess))
	FVector Acceleration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAnimInstance", meta = (AllowPrivateAccess))
	uint8 bIsFalling : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAnimInstance", meta = (AllowPrivateAccess))
	uint8 bIsCrouching : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ELocomotionState LocomotionState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EMovementDirection MovementDirection;


};