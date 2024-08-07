// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GWeaponActor.generated.h"

class UAnimInstance;
class UAnimMontage;
class UArrowComponent;

UCLASS()
class GAMEPROJECT_API AGWeaponActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGWeaponActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Public function to get Mesh
	//USkeletalMeshComponent* GetMesh() const { return Mesh; }
	UStaticMeshComponent* GetMesh() const { return Mesh; }

	//TSubclassOf<UAnimInstance> GetUnarmedCharacterAnimLayer() const { return UnarmedCharacterAnimLayer; }

	TSubclassOf<UAnimInstance> GetArmedCharacterAnimLayer() const { return ArmedCharacterAnimLayer; }

	int32 GetWeaponNumber() const { return WeaponNumber; }

	UArrowComponent* GetArrowSpawnArrowComponent() const { return DirectionArrow; }

	UAnimMontage* GetEquipAnimMontage() const { return EquipAnimMontage; }

	UAnimMontage* GetUnequipAnimMontage() const { return UnequipAnimMontage; }

	UAnimMontage* GetBasicAttackAnimMontage() const { return BasicAttackAnimMontage; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AGWeaponActor", meta = (AllowPrivateAccess))
	// TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AGWeaponActor", meta = (AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> Mesh;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGWeaponActor|AnimLayer", meta = (AllowPrivateAccess))
	//TSubclassOf<UAnimInstance> UnarmedCharacterAnimLayer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGWeaponActor|AnimLayer", meta = (AllowPrivateAccess))
	TSubclassOf<UAnimInstance> ArmedCharacterAnimLayer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGWeaponActor|AnimMontage", meta = (AllowPrivateAccess))
	TObjectPtr<UAnimMontage> EquipAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGWeaponActor|AnimMontage", meta = (AllowPrivateAccess))
	TObjectPtr<UAnimMontage> UnequipAnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGWeaponActor|AnimMontage", meta = (AllowPrivateAccess))
	TObjectPtr<UAnimMontage> BasicAttackAnimMontage;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "AGWeaponActor", meta = (AllowPrivateAccess))
	int32 WeaponNumber;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGWeaponActor", meta = (AllowPrivateAccess))
	TObjectPtr<UArrowComponent> DirectionArrow;
	
};