// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeBlackBoard/BlackBoardType/PZ_SkillTreeBlackboardType_bool.h"

#include "PZ_SkillTreeContext.h"


const UPZ_SkillTreeBlackboardType_bool::FDataType UPZ_SkillTreeBlackboardType_bool::InvalidValue = false;

UPZ_SkillTreeBlackboardType_bool::UPZ_SkillTreeBlackboardType_bool(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ValueSize = sizeof(uint8);
	SupportedOp = ESkillTreeBlackboardKeyOperation::Basic;
}

bool UPZ_SkillTreeBlackboardType_bool::GetValue(const UPZ_SkillTreeBlackboardType_bool* KeyOb, const uint8* RawData)
{
	return GetValueFromMemory<uint8>(RawData) != 0;
}

bool UPZ_SkillTreeBlackboardType_bool::SetValue(UPZ_SkillTreeBlackboardType_bool* KeyOb, uint8* RawData, bool bValue)
{
	return SetValueInMemory<uint8>(RawData, bValue);
}

ESkillTreeBlackboardCompare::Type UPZ_SkillTreeBlackboardType_bool::CompareValues(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock,
	const UPZ_SkillTreeBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const
{
	const bool MyValue = GetValue(this, MemoryBlock);
	const bool OtherValue = GetValue((UPZ_SkillTreeBlackboardType_bool*)OtherKeyOb, OtherMemoryBlock);

	return (MyValue == OtherValue) ? ESkillTreeBlackboardCompare::Equal : ESkillTreeBlackboardCompare::NotEqual;
}

FString UPZ_SkillTreeBlackboardType_bool::DescribeValue(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData) const
{
	return GetValue(this, RawData) ? TEXT("true") : TEXT("false");
}

bool UPZ_SkillTreeBlackboardType_bool::TestBasicOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeBasicKeyOperation::Type Op) const
{
	const bool Value = GetValue(this, MemoryBlock);
	return (Op == ESkillTreeBasicKeyOperation::Set) ? Value : !Value;
}
