// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeBlackBoard/BlackBoardType/PZ_SkillTreeBlackboardType_Int.h"

#include "PZ_SkillTreeContext.h"


const UPZ_SkillTreeBlackboardType_Int::FDataType UPZ_SkillTreeBlackboardType_Int::InvalidValue = UPZ_SkillTreeBlackboardType_Int::FDataType(0);


UPZ_SkillTreeBlackboardType_Int::UPZ_SkillTreeBlackboardType_Int(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ValueSize = sizeof(int32);
	SupportedOp = ESkillTreeBlackboardKeyOperation::Arithmetic;
}

int32 UPZ_SkillTreeBlackboardType_Int::GetValue(const UPZ_SkillTreeBlackboardType_Int* KeyOb, const uint8* RawData)
{

	return GetValueFromMemory<int32>(RawData);
}

bool UPZ_SkillTreeBlackboardType_Int::SetValue(UPZ_SkillTreeBlackboardType_Int* KeyOb, uint8* RawData, int32 Value)
{
	return SetValueInMemory<int32>(RawData, Value);
}


ESkillTreeBlackboardCompare::Type UPZ_SkillTreeBlackboardType_Int::CompareValues(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock,
	const UPZ_SkillTreeBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const
{
	const int32 MyValue = GetValue(this, MemoryBlock);
	const int32 OtherValue = GetValue((UPZ_SkillTreeBlackboardType_Int*)OtherKeyOb, OtherMemoryBlock);

	return (MyValue > OtherValue) ? ESkillTreeBlackboardCompare::Greater :
		(MyValue < OtherValue) ? ESkillTreeBlackboardCompare::Less :
		ESkillTreeBlackboardCompare::Equal;
}

FString UPZ_SkillTreeBlackboardType_Int::DescribeValue(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData) const
{
	return FString::Printf(TEXT("%d"), GetValue(this, RawData));
}

bool UPZ_SkillTreeBlackboardType_Int::TestArithmeticOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeArithmeticKeyOperation::Type Op, int32 OtherIntValue, float OtherFloatValue) const
{
	const int32 Value = GetValue(this, MemoryBlock);
	switch (Op)
	{
	case ESkillTreeArithmeticKeyOperation::Equal:			return (Value == OtherIntValue);
	case ESkillTreeArithmeticKeyOperation::NotEqual:			return (Value != OtherIntValue);
	case ESkillTreeArithmeticKeyOperation::Less:				return (Value < OtherIntValue);
	case ESkillTreeArithmeticKeyOperation::LessOrEqual:		return (Value <= OtherIntValue);
	case ESkillTreeArithmeticKeyOperation::Greater:			return (Value > OtherIntValue);
	case ESkillTreeArithmeticKeyOperation::GreaterOrEqual:	return (Value >= OtherIntValue);
	default: break;
	}

	return false;
}

FString UPZ_SkillTreeBlackboardType_Int::DescribeArithmeticParam(int32 IntValue, float FloatValue) const
{
	return FString::Printf(TEXT("%d"), IntValue);
}
