// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "SkillTreeBlackboardData.generated.h"

class UPZ_SkillTreeBlackboardKeyType;

/** blackboard entry definition */
USTRUCT(BlueprintType)
struct FSkillTreeBlackboardEntry
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, Category = Blackboard)
		FName EntryName;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = Blackboard, Meta = (ToolTip = "Optional description to explain what this blackboard entry does."))
		FString EntryDescription;
#endif // WITH_EDITORONLY_DATA

	/** key type and additional properties */
	UPROPERTY(EditAnywhere, Instanced, Category = Blackboard)
		UPZ_SkillTreeBlackboardKeyType* KeyType;

	/** if set to true then this field will be synchronized across all instances of this blackboard */
	UPROPERTY(EditAnywhere, Category = Blackboard)
		uint32 bInstanceSynced : 1;

	FSkillTreeBlackboardEntry()
		: KeyType(nullptr), bInstanceSynced(0)
	{}

	bool operator==(const FSkillTreeBlackboardEntry& Other) const;
};


USTRUCT()
struct FBlackboardInitializationData
{

	GENERATED_USTRUCT_BODY()


	FBlackboard::FKey KeyID;
	uint16 DataSize;

	FBlackboardInitializationData() {}
	FBlackboardInitializationData(FBlackboard::FKey InKeyID, uint16 InDataSize) : KeyID(InKeyID)
	{
		DataSize = (InDataSize <= 2) ? InDataSize : ((InDataSize + 3) & ~3);
	}

	struct FMemorySort
	{
		FORCEINLINE bool operator()(const FBlackboardInitializationData& A, const FBlackboardInitializationData& B) const
		{
			return A.DataSize > B.DataSize;
		}
	};
};
