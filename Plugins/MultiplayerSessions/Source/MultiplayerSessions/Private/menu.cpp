// Fill out your copyright notice in the Description page of Project Settings.


#include "menu.h"
#include "Components/Button.h"
#include "MultiplayerSessionSubsystem.h"

void Umenu::MenuSetup(int32 NumOfPublicConnections, FString TypeOfMatch)
{
	NumOfConnections = NumOfPublicConnections;
	MatchType = TypeOfMatch;
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	SetIsFocusable(true);

	UWorld* World = GetWorld();

	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		MultiplayerSessionSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionSubsystem>();
	}

	if (MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
	}
}

bool Umenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &ThisClass::HostButtonOnClick);
	}

	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinButtonOnClick);
	}
	return true;
}

void Umenu::NativeDestruct()
{
	Super::NativeDestruct();

	RemoveMenu();
}

void Umenu::OnCreateSession(bool bWasSuccessful)
{

}

void Umenu::HostButtonOnClick()
{
	UE_LOG(LogTemp, Error, TEXT("hostButtonClicked"));

	if (MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->CreateSession(NumOfConnections, MatchType);
		UWorld* world = GetWorld();
		if (world)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, FString(TEXT("Hosting session clicked")));
			}
			world->ServerTravel("/Game/ThirdPerson/Maps/Lobby?Listen");
		}
	}
}

void Umenu::JoinButtonOnClick()
{
	UE_LOG(LogTemp, Error, TEXT("JoinButtonClicked"));
}

void Umenu::RemoveMenu()
{
	RemoveFromParent();
	UWorld* world = GetWorld();
	if (world)
	{
		APlayerController* playerController = world->GetFirstPlayerController();
		if (playerController)
		{
			FInputModeGameOnly InputModeData;
			playerController->SetInputMode(InputModeData);
			playerController->SetShowMouseCursor(false);
		}
	}
}
