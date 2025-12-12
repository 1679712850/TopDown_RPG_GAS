// Copyright 13


#include "AbilitySystem/Ability/ProjectileSpellAbility.h"

#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"

void UProjectileSpellAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                              const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                              const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
}

void UProjectileSpellAbility::SpawnProjectile(const FGameplayAbilityActivationInfo ActivationInfo)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer)
	{
		return;	
	}

	if (auto CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(CombatInterface->GetCombatSocketLocation());

		//TODO: Set the Projectile Rotation
		
		auto Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		//TODO: Give the Projectile a Gameplay Effect Spec for causing Damage.
	
		Projectile->FinishSpawning(SpawnTransform);
	}
}
