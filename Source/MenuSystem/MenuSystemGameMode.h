// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MenuSystemGameMode.generated.h"

UCLASS(minimalapi)
class AMenuSystemGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMenuSystemGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

private:
	class UMultiplayerSessionSubsystem* MultiplayerSubsystem;
};



