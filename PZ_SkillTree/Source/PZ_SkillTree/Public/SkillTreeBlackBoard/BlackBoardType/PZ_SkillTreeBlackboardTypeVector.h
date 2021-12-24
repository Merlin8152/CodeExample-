// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "SkillTreeBlackBoard/PZ_SkillTreeBlackboardKeyType.h"
#include "PZ_SkillTreeBlackboardTypeVector.generated.h"

class UPZ_SkillTreeContext;

UCLASS(EditInlineNew, meta = (DisplayName = "Vector"))
class PZ_SKILLTREE_API UPZ_SkillTreeBlackboardTypeVector : public UPZ_SkillTreeBlackboardKeyType
{
	GENERATED_UCLASS_BODY()
	


	typedef FVector FDataType;
	static const FDataType InvalidValue;

	static FVector GetValue(const UPZ_SkillTreeBlackboardTypeVector* KeyOb, const uint8* RawData);
	static bool SetValue(UPZ_SkillTreeBlackboardTypeVector* KeyOb, uint8* RawData, const FVector& Value);


	virtual ESkillTreeBlackboardCompare::Type CompareValues(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock,
		const UPZ_SkillTreeBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const override;

protected:

	virtual void InitializeMemory(UPZ_SkillTreeContext& OwnerComp, uint8* RawData) override;
	virtual bool GetLocation(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData, FVector& Location) const override;
	virtual bool IsEmpty(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock) const override;
	virtual void Clear(UPZ_SkillTreeContext& OwnerComp, uint8* MemoryBlock) override;
	virtual FString DescribeValue(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData) const override;

};






