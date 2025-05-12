// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MultiplayerSessionSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMultiplayerSessionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UMultiplayerSessionSubsystem();

/// <summary>
/// To Handle Session Functionality, To be eventually called form the menu class
/// </summary>

	void CreateSession(int32 NumPublicConnections, FString MatchType);
	void FindSessions(int32 MaxSearchResults);
	void JoinSession(const FOnlineSessionSearchResult& SessionResult);
	void DestroySession();
	void StartSession();

protected:

	// Delegate Functions
	// 
	// Internal callbacks to the online session interface delegate list.
	// These functions wont be called outside this class
	//
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	void OnFindSessionsComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);


private:

	IOnlineSessionPtr SessionInterface;


	// Delegates
	// 
	// To Add to the online session delegate list
	// This shall be bound to the multiplayersessionsubsystem internal callbacks. 
	//

	FOnCreateSessionCompleteDelegate OnCreateSessionDelegate;
	FOnFindSessionsCompleteDelegate OnFindSessionsDelegate;
	FOnJoinSessionCompleteDelegate OnJoinSessionDelegate;
	FOnDestroySessionCompleteDelegate OnDestroySessionDelegate;
	FOnStartSessionCompleteDelegate OnStartSessionDelegate;
	
	//Delegate handles
	FDelegateHandle CreateSessionCompleteDelegateHandle,
					FindSessionsCompleteDelegateHandle,
					JoinSessionCompleteDelegateHandle,
					DestroySessionCompleteDelegateHandle,
					StartSessionCompleteDelegateHandle;
	
};
