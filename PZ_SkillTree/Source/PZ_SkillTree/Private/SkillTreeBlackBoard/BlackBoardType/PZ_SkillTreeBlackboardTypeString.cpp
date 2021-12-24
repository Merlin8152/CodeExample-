// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeBlackBoard/BlackBoardType/PZ_SkillTreeBlackboardTypeString.h"

#include "PZ_SkillTreeContext.h"


const UPZ_SkillTreeBlackboardTypeString::FDataType UPZ_SkillTreeBlackboardTypeString::InvalidValue = FString();


UPZ_SkillTreeBlackboardTypeString::UPZ_SkillTreeBlackboardTypeString(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ValueSize = 0;
	bCreateKeyInstance = true;

	SupportedOp = ESkillTreeBlackboardKeyOperation::Text;
}

FString UPZ_SkillTreeBlackboardTypeString::GetValue(const UPZ_SkillTreeBlackboardTypeString* KeyOb, const uint8* RawData)
{
	return KeyOb->StringValue;
}

bool UPZ_SkillTreeBlackboardTypeString::SetValue(UPZ_SkillTreeBlackboardTypeString* KeyOb, uint8* RawData, const FString& Value)
{
	const bool bChanged = !KeyOb->StringValue.Equals(Value);
	KeyOb->StringValue = Value;
	return bChanged;
}

ESkillTreeBlackboardCompare::Type UPZ_SkillTreeBlackboardTypeString::CompareValues(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock,
	const UPZ_SkillTreeBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const
{
	const FString MyValue = GetValue(this, MemoryBlock);
	const FString OtherValue = GetValue((UPZ_SkillTreeBlackboardTypeString*)OtherKeyOb, OtherMemoryBlock);

	return MyValue.Equals(OtherValue) ? ESkillTreeBlackboardCompare::Equal : ESkillTreeBlackboardCompare::NotEqual;
}

void UPZ_SkillTreeBlackboardTypeString::CopyValues(UPZ_SkillTreeContext& OwnerComp, uint8* MemoryBlock, const UPZ_SkillTreeBlackboardKeyType* SourceKeyOb, const uint8* SourceBlock)
{
	StringValue = ((UPZ_SkillTreeBlackboardTypeString*)SourceKeyOb)->StringValue;
}

FString UPZ_SkillTreeBlackboardTypeString::DescribeValue(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData) const
{
	return StringValue;
}

bool UPZ_SkillTreeBlackboardTypeString::TestTextOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeTextKeyOperation::Type Op, const FString& OtherString) const
{
	switch (Op)
	{
	case ETextKeyOperation::Equal:			return (StringValue == OtherString);
	case ETextKeyOperation::NotEqual:		return (StringValue != OtherString);
	case ETextKeyOperation::Contain:		return (StringValue.Contains(OtherString) == true);
	case ETextKeyOperation::NotContain:		return (StringValue.Contains(OtherString) == false);
	default: break;
	}

	return false;
}

void UPZ_SkillTreeBlackboardTypeString::Clear(UPZ_SkillTreeContext& OwnerComp, uint8* MemoryBlock)
{
	StringValue.Empty();
}

bool UPZ_SkillTreeBlackboardTypeString::IsEmpty(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock) const
{
	return StringValue.IsEmpty();
}
