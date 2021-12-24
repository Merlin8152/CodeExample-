// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "SkillTreeBlackBoard/PZ_SkillTreeBlackboardKeyType.h"
#include "PZ_SkillTreeBlackboardTypeRotate.generated.h"



class UPZ_SkillTreeContext;

UCLASS(EditInlineNew, meta = (DisplayName = "Rotator"))
class PZ_SKILLTREE_API UPZ_SkillTreeBlackboardTypeRotate : public UPZ_SkillTreeBlackboardKeyType
{
	GENERATED_UCLASS_BODY()


	typedef FRotator FDataType;
	static const FDataType InvalidValue;

	static FRotator GetValue(const UPZ_SkillTreeBlackboardTypeRotate* KeyOb, const uint8* RawData);
	static bool SetValue(UPZ_SkillTreeBlackboardTypeRotate* KeyOb, uint8* RawData, const FRotator& Value);

	virtual ESkillTreeBlackboardCompare::Type CompareValues(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock,
		const UPZ_SkillTreeBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const override;

protected:
	virtual void InitializeMemory(UPZ_SkillTreeContext& OwnerComp, uint8* RawData) override;
	virtual FString DescribeValue(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData) const override;
	virtual bool GetRotation(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData, FRotator& Rotation) const override;
	virtual bool IsEmpty(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData) const override;
	virtual void Clear(UPZ_SkillTreeContext& OwnerComp, uint8* RawData) override;
	virtual bool TestBasicOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeBasicKeyOperation::Type Op) const override;
};


