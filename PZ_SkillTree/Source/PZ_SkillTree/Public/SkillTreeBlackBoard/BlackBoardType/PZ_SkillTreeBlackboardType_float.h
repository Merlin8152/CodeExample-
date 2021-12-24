// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "SkillTreeBlackBoard/PZ_SkillTreeBlackboardKeyType.h"
#include "PZ_SkillTreeBlackboardType_float.generated.h"

class UPZ_SkillTreeContext;

UCLASS(EditInlineNew, meta = (DisplayName = "Float"))
class PZ_SKILLTREE_API UPZ_SkillTreeBlackboardType_float : public UPZ_SkillTreeBlackboardKeyType
{
	GENERATED_UCLASS_BODY()



	typedef float FDataType;
	static const FDataType InvalidValue;

	static int32 GetValue(const UPZ_SkillTreeBlackboardType_float* KeyOb, const uint8* RawData);
	static bool SetValue(UPZ_SkillTreeBlackboardType_float* KeyOb, uint8* RawData, float Value);

	virtual FString DescribeArithmeticParam(int32 IntValue, float FloatValue) const override;

	virtual ESkillTreeBlackboardCompare::Type CompareValues(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock,
		const UPZ_SkillTreeBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const override;

protected:
	virtual FString DescribeValue(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData) const override;
	virtual bool TestArithmeticOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeArithmeticKeyOperation::Type Op, int32 OtherIntValue, float OtherFloatValue) const override;

};


