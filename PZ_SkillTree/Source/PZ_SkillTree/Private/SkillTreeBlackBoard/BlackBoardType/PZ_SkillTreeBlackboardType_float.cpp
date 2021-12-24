// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeBlackBoard/BlackBoardType/PZ_SkillTreeBlackboardType_float.h"

#include "PZ_SkillTreeContext.h"


const UPZ_SkillTreeBlackboardType_float::FDataType UPZ_SkillTreeBlackboardType_float::InvalidValue = UPZ_SkillTreeBlackboardType_float::FDataType(0);


UPZ_SkillTreeBlackboardType_float::UPZ_SkillTreeBlackboardType_float(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ValueSize = sizeof(float);
	SupportedOp = ESkillTreeBlackboardKeyOperation::Arithmetic;
}

int32 UPZ_SkillTreeBlackboardType_float::GetValue(const UPZ_SkillTreeBlackboardType_float* KeyOb, const uint8* RawData)
{
	return GetValueFromMemory<float>(RawData);
}

bool UPZ_SkillTreeBlackboardType_float::SetValue(UPZ_SkillTreeBlackboardType_float* KeyOb, uint8* RawData, float Value)
{
	return SetValueInMemory<float>(RawData, Value);
}


ESkillTreeBlackboardCompare::Type UPZ_SkillTreeBlackboardType_float::CompareValues(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock,
	const UPZ_SkillTreeBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const
{
	const int32 MyValue = GetValue(this, MemoryBlock);
	const int32 OtherValue = GetValue((UPZ_SkillTreeBlackboardType_float*)OtherKeyOb, OtherMemoryBlock);

	return (MyValue > OtherValue) ? ESkillTreeBlackboardCompare::Greater :
		(MyValue < OtherValue) ? ESkillTreeBlackboardCompare::Less :
		ESkillTreeBlackboardCompare::Equal;
}

FString UPZ_SkillTreeBlackboardType_float::DescribeValue(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData) const
{
	return FString::Printf(TEXT("%d"), GetValue(this, RawData));
}

bool UPZ_SkillTreeBlackboardType_float::TestArithmeticOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeArithmeticKeyOperation::Type Op, int32 OtherIntValue, float OtherFloatValue) const
{
	const int32 Value = GetValue(this, MemoryBlock);
	switch (Op)
	{
	case ESkillTreeArithmeticKeyOperation::Equal:			return (Value == OtherIntValue);
	case ESkillTreeArithmeticKeyOperation::NotEqual:		return (Value != OtherIntValue);
	case ESkillTreeArithmeticKeyOperation::Less:			return (Value < OtherIntValue);
	case ESkillTreeArithmeticKeyOperation::LessOrEqual:		return (Value <= OtherIntValue);
	case ESkillTreeArithmeticKeyOperation::Greater:			return (Value > OtherIntValue);
	case ESkillTreeArithmeticKeyOperation::GreaterOrEqual:	return (Value >= OtherIntValue);
	default: break;
	}

	return false;
}

FString UPZ_SkillTreeBlackboardType_float::DescribeArithmeticParam(int32 IntValue, float FloatValue) const
{
	return FString::Printf(TEXT("%d"), IntValue);
}
