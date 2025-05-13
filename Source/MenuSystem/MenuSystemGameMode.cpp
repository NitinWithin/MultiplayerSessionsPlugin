// Copyright Epic Games, Inc. All Rights Reserved.

#include "MenuSystemGameMode.h"
#include "MenuSystemCharacter.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "UObject/ConstructorHelpers.h"

AMenuSystemGameMode::AMenuSystemGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AMenuSystemGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GameState)
	{
		int32 NumOfPlayers = GameState->PlayerArray.Num();     
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				1, 60.f, FColor::Yellow, FString::Printf(TEXT("Num of players in Lobby: %d"), NumOfPlayers));

			APlayerState* playerState = NewPlayer->GetPlayerState<APlayerState>();
			if (playerState)
			{
				FString playerName = playerState->GetPlayerName();
				GEngine->AddOnScreenDebugMessage(
					1, 60.f, FColor::Yellow, FString::Printf(TEXT("%s has joined the game"), *playerName));
			}
			
		}
	}


}

void AMenuSystemGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	APlayerState* playerState = Exiting->GetPlayerState<APlayerState>();
	if (playerState)
	{
		FString playerName = playerState->GetPlayerName();
		GEngine->AddOnScreenDebugMessage(
			1, 60.f, FColor::Yellow, FString::Printf(TEXT("%s has Left the game"), *playerName));
	}
}
