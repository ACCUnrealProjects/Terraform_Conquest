// Alex Chatt Terraform_Conquest 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TerraformGameMode.generated.h"

class AMain_Player_Controller;
class ACombat_AI_Con;
class ATerraformPlayerState;

/**
 * 
 */
UCLASS(config=Game)
class TERRAFORM_CONQUEST_API ATerraformGameMode : public AGameMode
{
	GENERATED_BODY()

private:

protected:

	// warm up time before match starts
	UPROPERTY(config)
		int32 WarmUpTime;

	// Time for the round
	UPROPERTY(config)
		int32 RoundTime;

	UPROPERTY(config)
		int32 TimeBetweenMatches;

	// General Point score
	UPROPERTY(config)
		int32 GeneralScore;

	// Kill score
	UPROPERTY(config)
		int32 KillScore;

	// Death Score
	UPROPERTY(config)
		int32 DeathScore;

	UPROPERTY(config)
		int32 MaxBotCount;

	UPROPERTY()
		TArray<ACombat_AI_Con*> BotControllers;

	UPROPERTY(config)
		TSubclassOf<AMain_Player_Controller> PlatformPlayerControllerClass;

	FTimerHandle TimerForUse;

	bool bNeedsBotCreation;

	bool bAllowBots;


public:

	/** The bot pawn classes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameMode)
		TArray<TSubclassOf<APawn>> BotPawnClasses;

private:

	/*
		UFUNCTION(exec)
		void SetAllowBots(bool bInAllowBots, int32 InMaxBots = 8);

		virtual void PreInitializeComponents() override;
	*/

	/** Initialize the game. This is called before actors' PreInitializeComponents. */
	//virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	/** Accept or reject a player attempting to join the server.  Fails login if you set the ErrorMessage to a non-empty string. */
	//virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	/** starts match warmup */
	//virtual void PostLogin(APlayerController* NewPlayer) override;

	/** Tries to spawn the player's pawn */
	//virtual void RestartPlayer(AController* NewPlayer) override;

	/** select best spawn point for player */
	//virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	/** always pick new random spawn */
	//virtual bool ShouldSpawnAtStartSpot(AController* Player) override;

	/** returns default pawn class for given controller */
	//virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	/** prevents friendly fire */
	//virtual float ModifyDamage(float Damage, AActor* DamagedActor, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) const;

	/** notify about kills */
	//virtual void Killed(AController* Killer, AController* KilledPlayer, APawn* KilledPawn, const UDamageType* DamageType);

	/** can players damage each other? */
	//virtual bool CanDealDamage(ATerraformPlayerState* DamageInstigator, ATerraformPlayerState* DamagedPlayer) const;

	/** always create cheat manager */
	//virtual bool AllowCheats(APlayerController* P) override;

	/** update remaining time */
	//virtual void DefaultTimer();

	/** called before startmatch */
	//virtual void HandleMatchIsWaitingToStart() override;

	/** starts new match */
	//virtual void HandleMatchHasStarted() override;

	/** new player joins */
	//virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	/** hides the onscreen hud and restarts the map */
	//virtual void RestartGame() override;

	/** Creates AIControllers for all bots */
	//void CreateBotControllers();

	/** Create a bot */
	//ACombat_AI_Con* CreateBot(int32 BotNum);

	//virtual void PostInitProperties() override;

protected:

	/** spawning all bots for this game */
	//void StartBots();

	/** initialization for bot after creation */
	//virtual void InitBot(AShooterAIController* AIC, int32 BotNum);

	/** check who won */
	//virtual void DetermineMatchWinner();

	/** check if PlayerState is a winner */
	//virtual bool IsWinner(AShooterPlayerState* PlayerState) const;

	/** check if player can use spawnpoint */
	//virtual bool IsSpawnpointAllowed(APlayerStart* SpawnPoint, AController* Player) const;

	/** check if player should use spawnpoint */
	//virtual bool IsSpawnpointPreferred(APlayerStart* SpawnPoint, AController* Player) const;

	/** Returns game session class to use */
	//virtual TSubclassOf<AGameSession> GetGameSessionClass() const override;

public:

	ATerraformGameMode();

	virtual void StartPlay() override;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "CreatePlayerPawn"))
	void CreatePlayerPawn(TSubclassOf <class APawn> PawnType, APlayerController* PCon, FTransform SpawnTransform);
	
	/** finish current match and lock players */
	//UFUNCTION(exec)
		//void FinishMatch();

	/* Finishes the match and bumps everyone to main menu.*/
	/* Only GameInstance should call this function */
	//void RequestFinishAndExitToMainMenu();

	/** get the name of the bots count option used in server travel URL */
	//static FString GetBotsCountOptionName();
	
};
