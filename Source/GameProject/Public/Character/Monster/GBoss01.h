// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/GMonster.h"
#include "GBoss01.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPROJECT_API AGBoss01 : public AGMonster
{
	GENERATED_BODY()

public:
	AGBoss01();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	virtual void DrawDetectLine(const bool bResult, FVector CenterPosition, float DetectRadius, FVector PCLocation, FVector MonsterLocation) override;
	
	UFUNCTION(NetMulticast, Unreliable)
	virtual void DrawDetectLine_NetMulticast(const bool bResult, FVector CenterPosition, float DetectRadius, FVector PCLocation, FVector MonsterLocation);
	
protected:
	// Attack
	virtual void OnCheckHit() override;// AN
	
	virtual void OnCheckHitDown() override;// AN

	// Basic Attack
	virtual void BeginAttack() override;

	UFUNCTION(NetMulticast, Reliable)
	void PlayBasicAttackAnimMontage_NetMulticast(uint16 InRandNum);

	UFUNCTION(NetMulticast, Reliable)
	void DrawLine_NetMulticast(const bool bResult, ECheckHitDirection InCheckHitDirection);

	virtual void EndAttack(class UAnimMontage* InMontage, bool bInterruped) override;

	// Jump Attack
	virtual void BeginJumpAttack() override;

	UFUNCTION(NetMulticast, Reliable)
	void PlayJumpAttackAnimMontage_NetMulticast();

	UFUNCTION(NetMulticast, Reliable)
	void PlayLastSectionJumpAttackAnimMontage_NetMulticast();
	
	virtual void EndJumpAttack(UAnimMontage* InMontage, bool bInterruped) override;

	// Shoot
	virtual void OnShootProjectile() override;// AN
	
	virtual void OnShootWindProjectile() override;// AN
	
	virtual void OnShootMultipleProjectile() override;// AN

	virtual void OnShootAOE() override;// AN

	virtual void OnShootShapeAOE() override;// AN
	
	virtual void OnShootLaser() override;// AN
	
	virtual void OnShootTorus() override;// AN

	// Shoot Basic
	virtual void BeginShoot() override;

	UFUNCTION(NetMulticast, Reliable)
	void PlayShootAnimMontage_NetMulticast();

	virtual void EndShoot(class UAnimMontage* InMontage, bool bInterruped) override;

	// Shoot Wind
	virtual void BeginShootWind() override;

	UFUNCTION(NetMulticast, Reliable)
	void PlayShootWindAnimMontage_NetMulticast();

	virtual void EndShootWind(class UAnimMontage* InMontage, bool bInterruped) override;

	// Shoot Multiple
	virtual void BeginShootMultiple() override;

	UFUNCTION(NetMulticast, Reliable)
	void PlayShootMultipleAnimMontage_NetMulticast();

	virtual void EndShootMultiple(class UAnimMontage* InMontage, bool bInterruped) override;

	// Shoot AOE
	virtual void BeginShootAOE() override;

	UFUNCTION(NetMulticast, Reliable)
	void PlayShootAOEAnimMontage_NetMulticast();

	virtual void EndShootAOE(UAnimMontage* InMontage, bool bInterruped) override;

	// Shoot Laser
	virtual void BeginShootLaser() override;

	UFUNCTION(NetMulticast, Reliable)
	void PlayShootLaserAnimMontage_NetMulticast();

	virtual void EndShootLaser(UAnimMontage* InMontage, bool bInterruped) override;

	UFUNCTION()
	void OnLaserShrinkEnd();
	
	UFUNCTION(NetMulticast, Reliable)
	void PlayShootLaserFinishAnimMontage_NetMulticast();

	void EndShootLaserFinish(UAnimMontage* InMontage, bool bInterruped);

	// Shoot Torus
	virtual void BeginShootTorus() override;

	UFUNCTION(NetMulticast, Reliable)
	void PlayShootTorusAnimMontage_NetMulticast();

	virtual void EndShootTorus(UAnimMontage* InMontage, bool bInterruped) override;

	// Jump
	virtual void OnJump() override;// AN

	virtual void Landed(const FHitResult& Hit) override;

	// Teleport
	virtual void Teleport() override;
	
	UFUNCTION(NetMulticast, Reliable)
	void Teleport_NetMulticast();
	
	virtual void TeleportEnd() override;

	UFUNCTION(NetMulticast, Reliable)
	void TeleportEnd_NetMulticast();
	
	// Shout
	virtual void BeginShout() override;
	
	UFUNCTION(NetMulticast, Reliable)
	void PlayShoutAnimMontage_NetMulticast();
	
	virtual void EndShout(UAnimMontage* InMontage, bool bInterruped) override;

	// HitReact
	//// Ragdoll
	UFUNCTION(NetMulticast, Reliable)
	void ExecuteHitRagdoll_NetMulticast(FName InPivotBoneName, float InBlendWeight);

	UFUNCTION()
    void ActivateHitRagdoll(FName InPivotBoneName, float InBlendWeight);
	
	UFUNCTION()
	void OnHitRagdollRestoreTimerElapsed(FName InPivotBoneName, float InBlendWeight);

	UFUNCTION()
	void UpdateHitRagdollBlend(FName InPivotBoneName, float InBlendWeight);

	UFUNCTION()
	void DeactivateHitRagdoll(FName InPivotBoneName);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|HitReact", meta = (AllowPrivateAccess))
	uint8 bIsRagdollActive;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|HitReact", meta = (AllowPrivateAccess))
	float CurrentBlendWeight = 1.f;
	
	FTimerHandle HitRagdollRestoreTimerHandle;

	FTimerDelegate HitRagdollRestoreTimerDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|HitReact", meta = (AllowPrivateAccess))
	float HitRagdollRestoreThreshold = 1.f;
	
	FTimerHandle PhysicsBlendTimerHandle;
	
	FTimerDelegate PhysicsBlendTimerDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|HitReact", meta = (AllowPrivateAccess))
	float PhysicsBlendTimerRate = 0.03f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|HitReact", meta = (AllowPrivateAccess))
	float PhysicsBlendInterpSpeed = 20.f;
	
	//// Stun
	UFUNCTION(NetMulticast, Reliable)
	void PlayStunHitReactAnimMontage_NetMulticast();

	virtual void EndStunHitReact(class UAnimMontage* InMontage, bool bInterrupted);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|HitReact", meta = (AllowPrivateAccess))
	TObjectPtr<class UAnimMontage> StunHitReactMontage;

	//// KnockDown
	UFUNCTION(NetMulticast, Reliable)
	void PlayKnockDownHitReactAnimMontage_NetMulticast();

	virtual void EndKnockDownHitReact(class UAnimMontage* InMontage, bool bInterrupted);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|HitReact", meta = (AllowPrivateAccess))
	TObjectPtr<class UAnimMontage> KnockDownHitReactMontage;

	//// AirBound
	UFUNCTION(NetMulticast, Reliable)
	void PlayAirBoundHitReactAnimMontage_NetMulticast();

	virtual void EndAirBoundHitReact(class UAnimMontage* InMontage, bool bInterrupted);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|HitReact", meta = (AllowPrivateAccess))
	TObjectPtr<class UAnimMontage> AirBoundHitReactMontage;

	//// GroundBound
	UFUNCTION(NetMulticast, Reliable)
	void PlayGroundBoundHitReactAnimMontage_NetMulticast();

	virtual void EndGroundBoundHitReact(class UAnimMontage* InMontage, bool bInterrupted);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|HitReact", meta = (AllowPrivateAccess))
	TObjectPtr<class UAnimMontage> GroundBoundHitReactMontage;
	
	virtual void OnStartLying() override;// AN

	void ForceCall_EndMontageFunction();

protected:
	// BodyMesh
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Body", meta = (AllowPrivateAccess))
	TObjectPtr<class USkeletalMeshComponent> ClothMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Body", meta = (AllowPrivateAccess))
	TObjectPtr<class USkeletalMeshComponent> BeardMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Body", meta = (AllowPrivateAccess))
	TObjectPtr<class USkeletalMeshComponent> Armor01MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Body", meta = (AllowPrivateAccess))
	TObjectPtr<class USkeletalMeshComponent> Armor02MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Body", meta = (AllowPrivateAccess))
	TObjectPtr<class USkeletalMeshComponent> Armor03MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Body", meta = (AllowPrivateAccess))
	TObjectPtr<class USkeletalMeshComponent> Armor04MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Body", meta = (AllowPrivateAccess))
	TObjectPtr<class USkeletalMeshComponent> Armor05MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Body", meta = (AllowPrivateAccess))
	TObjectPtr<class USkeletalMeshComponent> Armor06MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Body", meta = (AllowPrivateAccess))
	TObjectPtr<class USkeletalMeshComponent> Armor07MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Body", meta = (AllowPrivateAccess))
	TObjectPtr<class USkeletalMeshComponent> Armor08MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Body", meta = (AllowPrivateAccess))
	TObjectPtr<class USkeletalMeshComponent> Armor09MeshComponent;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Weapon", meta = (AllowPrivateAccess))
	// TObjectPtr<class UStaticMeshComponent> WeaponMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Weapon", meta = (AllowPrivateAccess))
	TObjectPtr<class USceneComponent> MultipleProjectileLaunchComponent1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Weapon", meta = (AllowPrivateAccess))
	TObjectPtr<class USceneComponent> MultipleProjectileLaunchComponent2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Weapon", meta = (AllowPrivateAccess))
	TObjectPtr<class USceneComponent> MultipleProjectileLaunchComponent3;

	// Attack
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Attack", meta = (AllowPrivateAccess))
	float BasicAttackRange = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Attack", meta = (AllowPrivateAccess))
	float BasicAttackRadius = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Attack", meta = (AllowPrivateAccess))
	float DownAttackRange = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Attack", meta = (AllowPrivateAccess))
	float DownAttackRadius = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Attack", meta = (AllowPrivateAccess))
	float BasicAttackDamage = 5.f;

	uint16 PreviousAttackRandNum;

public:
	TArray<uint8> PreviousPatternAttackRandNum;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Attack", meta = (AllowPrivateAccess))
	TObjectPtr<class UAnimMontage> Attack01Montage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Attack", meta = (AllowPrivateAccess))
	TObjectPtr<class UAnimMontage> Attack02Montage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Attack", meta = (AllowPrivateAccess))
	TObjectPtr<class UAnimMontage> Attack03Montage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Attack", meta = (AllowPrivateAccess))
	TObjectPtr<class UAnimMontage> Attack04Montage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Attack", meta = (AllowPrivateAccess))
	TObjectPtr<class UAnimMontage> JumpAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Attack", meta = (AllowPrivateAccess))
	TObjectPtr<class UAnimMontage> ShootMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Attack", meta = (AllowPrivateAccess))
	TObjectPtr<class UAnimMontage> ShootWindMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Attack", meta = (AllowPrivateAccess))
	TObjectPtr<class UAnimMontage> ShootMultipleMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Attack", meta = (AllowPrivateAccess))
	TObjectPtr<class UAnimMontage> ShootAOEMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Attack", meta = (AllowPrivateAccess))
	TObjectPtr<class UAnimMontage> ShootLaserMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Attack", meta = (AllowPrivateAccess))
	TObjectPtr<class UAnimMontage> ShootLaserFinishMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Attack", meta = (AllowPrivateAccess))
	TObjectPtr<class UAnimMontage> ShootTorusMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Attack", meta = (AllowPrivateAccess))
	TObjectPtr<class UAnimMontage> ShoutMontage;

	// Weapon
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Weapon", meta = (AllowPrivateAccess))
	TSubclassOf<class AGWeaponActor> WeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AGBoss01|Weapon", meta = (AllowPrivateAccess))
	TObjectPtr<class AGWeaponActor> WeaponInstance;

	// Teleport
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Particle", meta = (AllowPrivateAccess))
	TObjectPtr<class UParticleSystem> TeleportBodyEffectEmitterTemplate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AGBoss01|Particle", meta = (AllowPrivateAccess))
	TObjectPtr<class UParticleSystemComponent> TeleportBodyEffectEmitterInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Particle", meta = (AllowPrivateAccess))
	TObjectPtr<class UParticleSystem> TeleportTrailEffectEmitterTemplate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AGBoss01|Particle", meta = (AllowPrivateAccess))
	TObjectPtr<class UParticleSystemComponent> TeleportTrailEffectEmitterInstance;

	FTimerHandle TeleportEndDelayTimerHandle;

	float TeleportEndDelayThreshold = 0.5f;

	// Jump
	FString JumpAttackAnimMontageEndSectionName = FString(TEXT("END"));

	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|UI", meta = (AllowPrivateAccess))
	// TObjectPtr<class UGW_HPBar> BossHPBarWidgetRef;
	//
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|UI", meta = (AllowPrivateAccess))
	// TSubclassOf<class UGW_HPBar> BossHPBarWidgetTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Weapon", meta = (AllowPrivateAccess))
	TSubclassOf<class AGSpinningProjectileActor> ProjectileClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Weapon", meta = (AllowPrivateAccess))
	TSubclassOf<class AGWindProjectileActor> WindProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Weapon", meta = (AllowPrivateAccess))
	TSubclassOf<class AGHomingProjectileActor> MultipleProjectileClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Weapon", meta = (AllowPrivateAccess))
	TSubclassOf<class AGAOEActor> AOEClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AGBoss01|Weapon", meta = (AllowPrivateAccess))
	TObjectPtr<class AGLaserActor> LaserInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Weapon", meta = (AllowPrivateAccess))
	TSubclassOf<class AGLaserActor> LaserClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Weapon", meta = (AllowPrivateAccess))
	TObjectPtr<class USceneComponent> LaserLaunchComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Weapon", meta = (AllowPrivateAccess))
	TSubclassOf<class AGTorusActor> TorusClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AGBoss01|Weapon", meta = (AllowPrivateAccess))
	TObjectPtr<class USceneComponent> TorusLaunchComponent;
	
};
