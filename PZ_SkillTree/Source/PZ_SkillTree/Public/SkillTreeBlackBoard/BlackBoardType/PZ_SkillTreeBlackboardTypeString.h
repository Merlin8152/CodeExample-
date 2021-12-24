// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "SkillTreeBlackBoard/PZ_SkillTreeBlackboardKeyType.h"
#include "PZ_SkillTreeBlackboardTypeString.generated.h"

class UPZ_SkillTreeContext;

UCLASS(EditInlineNew, meta = (DisplayName = "String"))
class PZ_SKILLTREE_API UPZ_SkillTreeBlackboardTypeString : public UPZ_SkillTreeBlackboardKeyType
{
	GENERATED_UCLASS_BODY()

	typedef FString FDataType;
	static const FDataType InvalidValue;

	static FString GetValue(const UPZ_SkillTreeBlackboardTypeString* KeyOb, const uint8* RawData);
	static bool SetValue(UPZ_SkillTreeBlackboardTypeString* KeyOb, uint8* RawData, const FString& Value);


	virtual ESkillTreeBlackboardCompare::Type CompareValues(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock,
		const UPZ_SkillTreeBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const override;


	UPROPERTY()
		FString StringValue;

protected:
	virtual FString DescribeValue(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData) const override;
	virtual bool TestTextOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeTextKeyOperation::Type Op, const FString& OtherString) const override;
	virtual void Clear(UPZ_SkillTreeContext& OwnerComp, uint8* MemoryBlock) override;
	virtual bool IsEmpty(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock) const override;
	virtual void CopyValues(UPZ_SkillTreeContext& OwnerComp, uint8* MemoryBlock, const UPZ_SkillTreeBlackboardKeyType* SourceKeyOb, const uint8* SourceBlock) override;

};






