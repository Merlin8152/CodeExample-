// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeBlackBoard/BlackBoardType/PZ_SkillTreeBlackboardType_Name.h"

#include "PZ_SkillTreeContext.h"


const UPZ_SkillTreeBlackboardType_Name::FDataType UPZ_SkillTreeBlackboardType_Name::InvalidValue = NAME_None;


UPZ_SkillTreeBlackboardType_Name::UPZ_SkillTreeBlackboardType_Name(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ValueSize = sizeof(FName);
	SupportedOp = ESkillTreeBlackboardKeyOperation::Text;
}

FName UPZ_SkillTreeBlackboardType_Name::GetValue(const UPZ_SkillTreeBlackboardType_Name* KeyOb, const uint8* RawData)
{
	return GetValueFromMemory<FName>(RawData);
}

bool UPZ_SkillTreeBlackboardType_Name::SetValue(UPZ_SkillTreeBlackboardType_Name* KeyOb, uint8* RawData, const FName& Value)
{
	return SetValueInMemory<FName>(RawData, Value);
}

ESkillTreeBlackboardCompare::Type UPZ_SkillTreeBlackboardType_Name::CompareValues(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock,
	const UPZ_SkillTreeBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const
{
	const FName MyValue = GetValue(this, MemoryBlock);
	const FName OtherValue = GetValue((UPZ_SkillTreeBlackboardType_Name*)OtherKeyOb, OtherMemoryBlock);

	return (MyValue == OtherValue) ? ESkillTreeBlackboardCompare::Equal : ESkillTreeBlackboardCompare::NotEqual;
}

FString UPZ_SkillTreeBlackboardType_Name::DescribeValue(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData) const
{
	return GetValue(this, RawData).ToString();
}

bool UPZ_SkillTreeBlackboardType_Name::TestTextOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeTextKeyOperation::Type Op, const FString& OtherString) const
{
	const FString Value = GetValue(this, MemoryBlock).ToString();
	switch (Op)
	{
	case ETextKeyOperation::Equal:			return (Value == OtherString);
	case ETextKeyOperation::NotEqual:		return (Value != OtherString);
	case ETextKeyOperation::Contain:		return (Value.Contains(OtherString) == true);
	case ETextKeyOperation::NotContain:		return (Value.Contains(OtherString) == false);
	default: break;
	}

	return false;
}
