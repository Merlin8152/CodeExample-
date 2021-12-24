// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "SkillTreeBlackBoard/PZ_SkillTreeBlackboardKeyType.h"
#include "PZ_SkillTreeBlackboardType_Name.generated.h"


class UPZ_SkillTreeContext;


UCLASS(EditInlineNew, meta = (DisplayName = "Name"))
class PZ_SKILLTREE_API UPZ_SkillTreeBlackboardType_Name : public UPZ_SkillTreeBlackboardKeyType
{
	GENERATED_UCLASS_BODY()

	typedef FName FDataType;
	static const FDataType InvalidValue;


	static FName GetValue(const UPZ_SkillTreeBlackboardType_Name* KeyOb, const uint8* RawData);
	static bool SetValue(UPZ_SkillTreeBlackboardType_Name* KeyOb, uint8* RawData, const FName& Value);

	virtual ESkillTreeBlackboardCompare::Type CompareValues(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock,
		const UPZ_SkillTreeBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const override;

protected:
	virtual FString DescribeValue(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData) const override;
	virtual bool TestTextOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeTextKeyOperation::Type Op, const FString& OtherString) const override;


};




