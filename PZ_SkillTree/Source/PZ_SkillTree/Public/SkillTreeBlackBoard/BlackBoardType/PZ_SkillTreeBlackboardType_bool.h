// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "SkillTreeBlackBoard/PZ_SkillTreeBlackboardKeyType.h"
#include "PZ_SkillTreeBlackboardType_bool.generated.h"

class UPZ_SkillTreeContext;

UCLASS(EditInlineNew, meta = (DisplayName = "Bool"))
class PZ_SKILLTREE_API UPZ_SkillTreeBlackboardType_bool : public UPZ_SkillTreeBlackboardKeyType
{
	GENERATED_UCLASS_BODY()


	typedef bool FDataType;
	static const FDataType InvalidValue;

	static bool GetValue(const UPZ_SkillTreeBlackboardType_bool* KeyOb, const uint8* RawData);
	static bool SetValue(UPZ_SkillTreeBlackboardType_bool* KeyOb, uint8* RawData, bool Value);

	virtual ESkillTreeBlackboardCompare::Type CompareValues(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock,
		const UPZ_SkillTreeBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const override;

protected:

	virtual FString DescribeValue(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData) const override;
	virtual bool TestBasicOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeBasicKeyOperation::Type Op) const override;

};




