// Copyright 13


#include "AbilitySystem/Ability/ProjectileSpellAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"

void UProjectileSpellAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                              const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                              const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
}

FString UProjectileSpellAbility::GetDescription(int32 Level)
{
	const int32 Damage = GetDamageByDamageType(Level, FAuraGameplayTags::Get().Damage_Fire);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>FIRE BOLT</>\n\n"

			// Level
			"<Small>Level: </><Level>%d</>\n"
			// ManaCost
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			// Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"
			
			"<Default>Launches a bolt of fire, "
			"exploding on impact and dealing: </>"

			// Damage
			"<Damage>%d</><Default> fire damage with"
			" a chance to burn</>"),

			// Values
			Level,
			ManaCost,
			Cooldown,
			Damage);
	}
	else
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>FIRE BOLT</>\n\n"

			// Level
			"<Small>Level: </><Level>%d</>\n"
			// ManaCost
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			// Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			// Number of FireBolts
			"<Default>Launches %d bolts of fire, "
			"exploding on impact and dealing: </>"

			// Damage
			"<Damage>%d</><Default> fire damage with"
			" a chance to burn</>"),

			// Values
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, NumProjectiles),
			Damage);
		
	}
}

FString UProjectileSpellAbility::GetNextLevelDescription(int32 Level)
{
	const int32 Damage = GetDamageByDamageType(Level, FAuraGameplayTags::Get().Damage_Fire);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT(
			// Title
			"<Title>NEXT LEVEL: </>\n\n"

			// Level
			"<Small>Level: </><Level>%d</>\n"
			// ManaCost
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			// Cooldown
			"<Small>Cooldown: </><Cooldown>%.1f</>\n\n"

			// Number of FireBolts
			"<Default>Launches %d bolts of fire, "
			"exploding on impact and dealing: </>"

			// Damage
			"<Damage>%d</><Default> fire damage with"
			" a chance to burn</>"),

			// Values
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, NumProjectiles),
			Damage);
}

void UProjectileSpellAbility::SpawnProjectile(const FVector& TargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch , float PitchOverride)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer)
	{
		return;	
	}
	
	auto SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(
		GetAvatarActorFromActorInfo(),
		SocketTag);

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	
	auto Rotation = (TargetLocation - SocketLocation).Rotation();
	if (bOverridePitch)
	{
		Rotation.Pitch = PitchOverride;
	}
	SpawnTransform.SetRotation(Rotation.Quaternion());
	
	auto Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());

	FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	for (auto& Pair : DamageTypes)
	{
		const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, ScaledDamage);
	}
	Projectile->DamageEffectSpecHandle = SpecHandle;

	Projectile->FinishSpawning(SpawnTransform);
}
