// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeBlackBoard/PZ_SkillTreeBlackboardKeyType.h"

#include "PZ_SkillTreeContext.h"


UPZ_SkillTreeBlackboardKeyType::UPZ_SkillTreeBlackboardKeyType(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ValueSize = 0;
	SupportedOp = ESkillTreeBlackboardKeyOperation::Basic;
	bCreateKeyInstance = false;
	bIsInstanced = false;
}

void UPZ_SkillTreeBlackboardKeyType::PreInitialize(UPZ_SkillTreeContext& OwnerComp)
{
	// empty in base class
}

void UPZ_SkillTreeBlackboardKeyType::InitializeKey(UPZ_SkillTreeContext& OwnerComp, FBlackboard::FKey KeyID)
{
	uint8* RawData = OwnerComp.GetKeyRawData(KeyID);

	if (bCreateKeyInstance)
	{
		FSkillTreeBlackboardInstancedKeyMemory* MyMemory = (FSkillTreeBlackboardInstancedKeyMemory*)RawData;
		UPZ_SkillTreeBlackboardKeyType* KeyInstance = NewObject<UPZ_SkillTreeBlackboardKeyType>(&OwnerComp, GetClass());
		KeyInstance->bIsInstanced = true;
		MyMemory->KeyIdx = KeyID;
		OwnerComp.KeyInstances[KeyID] = KeyInstance;

		uint8* InstanceMemoryBlock = RawData + sizeof(FSkillTreeBlackboardInstancedKeyMemory);
		KeyInstance->InitializeMemory(OwnerComp, InstanceMemoryBlock);
	}
	else
	{
		InitializeMemory(OwnerComp, RawData);
	}
}

UPZ_SkillTreeBlackboardKeyType* UPZ_SkillTreeBlackboardKeyType::GetKeyInstance(UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock) const
{
	FSkillTreeBlackboardInstancedKeyMemory* MyMemory = (FSkillTreeBlackboardInstancedKeyMemory*)MemoryBlock;
	return MyMemory && OwnerComp.KeyInstances.IsValidIndex(MyMemory->KeyIdx) ?
		OwnerComp.KeyInstances[MyMemory->KeyIdx] : NULL;
}

const UPZ_SkillTreeBlackboardKeyType* UPZ_SkillTreeBlackboardKeyType::GetKeyInstance(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock) const
{
	FBlackboardInstancedKeyMemory* MyMemory = (FBlackboardInstancedKeyMemory*)MemoryBlock;
	return MyMemory && OwnerComp.KeyInstances.IsValidIndex(MyMemory->KeyIdx) ?
		OwnerComp.KeyInstances[MyMemory->KeyIdx] : NULL;
}

void UPZ_SkillTreeBlackboardKeyType::InitializeMemory(UPZ_SkillTreeContext& OwnerComp, uint8* MemoryBlock)
{
	// empty in base class
}

void UPZ_SkillTreeBlackboardKeyType::WrappedFree(UPZ_SkillTreeContext& OwnerComp, uint8* MemoryBlock)
{
	if (HasInstance())
	{
		UPZ_SkillTreeBlackboardKeyType* InstancedKey = GetKeyInstance(OwnerComp, MemoryBlock);
		uint8* InstanceMemoryBlock = MemoryBlock + sizeof(FBlackboardInstancedKeyMemory);
		InstancedKey->FreeMemory(OwnerComp, InstanceMemoryBlock);
	}

	return FreeMemory(OwnerComp, MemoryBlock);
}

void UPZ_SkillTreeBlackboardKeyType::FreeMemory(UPZ_SkillTreeContext& OwnerComp, uint8* MemoryBlock)
{
	// empty in base class
}

bool UPZ_SkillTreeBlackboardKeyType::WrappedGetLocation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, FVector& Location) const
{
	if (HasInstance())
	{
		const UPZ_SkillTreeBlackboardKeyType* InstancedKey = GetKeyInstance(OwnerComp, MemoryBlock);
		const uint8* InstanceMemoryBlock = MemoryBlock + sizeof(FBlackboardInstancedKeyMemory);
		return InstancedKey->GetLocation(OwnerComp, InstanceMemoryBlock, Location);
	}

	return GetLocation(OwnerComp, MemoryBlock, Location);
}

bool UPZ_SkillTreeBlackboardKeyType::GetLocation(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData, FVector& Location) const
{
	return false;
}

bool UPZ_SkillTreeBlackboardKeyType::WrappedGetRotation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, FRotator& Rotation) const
{
	if (HasInstance())
	{
		const UPZ_SkillTreeBlackboardKeyType* InstancedKey = GetKeyInstance(OwnerComp, MemoryBlock);
		const uint8* InstanceMemoryBlock = MemoryBlock + sizeof(FBlackboardInstancedKeyMemory);
		return InstancedKey->GetRotation(OwnerComp, InstanceMemoryBlock, Rotation);
	}

	return GetRotation(OwnerComp, MemoryBlock, Rotation);
}

bool UPZ_SkillTreeBlackboardKeyType::GetRotation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, FRotator& Rotation) const
{
	return false;
}

void UPZ_SkillTreeBlackboardKeyType::WrappedClear(const UPZ_SkillTreeContext& OwnerComp, uint8* MemoryBlock) const
{
	UPZ_SkillTreeContext& MutableOwner = (UPZ_SkillTreeContext&)OwnerComp;
	if (HasInstance())
	{
		UPZ_SkillTreeBlackboardKeyType* InstancedKey = GetKeyInstance(MutableOwner, MemoryBlock);
		uint8* InstanceMemoryBlock = MemoryBlock + sizeof(FBlackboardInstancedKeyMemory);
		InstancedKey->Clear(MutableOwner, InstanceMemoryBlock);
	}
	else
	{
		UPZ_SkillTreeBlackboardKeyType* MutableKey = (UPZ_SkillTreeBlackboardKeyType*)this;
		MutableKey->Clear(MutableOwner, MemoryBlock);
	}
}

void UPZ_SkillTreeBlackboardKeyType::Clear(UPZ_SkillTreeContext& OwnerComp, uint8* MemoryBlock)
{
	FMemory::Memzero(MemoryBlock, GetValueSize());
}

bool UPZ_SkillTreeBlackboardKeyType::WrappedIsEmpty(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock) const
{
	if (HasInstance())
	{
		const UPZ_SkillTreeBlackboardKeyType* InstancedKey = GetKeyInstance(OwnerComp, MemoryBlock);
		const uint8* InstanceMemoryBlock = MemoryBlock + sizeof(FBlackboardInstancedKeyMemory);
		return InstancedKey->IsEmpty(OwnerComp, InstanceMemoryBlock);
	}

	return IsEmpty(OwnerComp, MemoryBlock);
}

bool UPZ_SkillTreeBlackboardKeyType::IsEmpty(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock) const
{
	for (int32 ByteIndex = 0; ByteIndex < GetValueSize(); ++ByteIndex)
	{
		if (MemoryBlock[ByteIndex] != uint8(0))
		{
			return false;
		}
	}

	return true;
}

bool UPZ_SkillTreeBlackboardKeyType::WrappedTestBasicOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeBasicKeyOperation::Type Op) const
{
	if (HasInstance())
	{
		const UPZ_SkillTreeBlackboardKeyType* InstancedKey = GetKeyInstance(OwnerComp, MemoryBlock);
		const uint8* InstanceMemoryBlock = MemoryBlock + sizeof(FBlackboardInstancedKeyMemory);
		return InstancedKey->TestBasicOperation(OwnerComp, InstanceMemoryBlock, Op);
	}

	return TestBasicOperation(OwnerComp, MemoryBlock, Op);
}

bool UPZ_SkillTreeBlackboardKeyType::TestBasicOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeBasicKeyOperation::Type Op) const
{
	return false;
}

bool UPZ_SkillTreeBlackboardKeyType::WrappedTestArithmeticOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeArithmeticKeyOperation::Type Op, int32 OtherIntValue, float OtherFloatValue) const
{
	if (HasInstance())
	{
		const UPZ_SkillTreeBlackboardKeyType* InstancedKey = GetKeyInstance(OwnerComp, MemoryBlock);
		const uint8* InstanceMemoryBlock = MemoryBlock + sizeof(FBlackboardInstancedKeyMemory);
		return InstancedKey->TestArithmeticOperation(OwnerComp, InstanceMemoryBlock, Op, OtherIntValue, OtherFloatValue);
	}

	return TestArithmeticOperation(OwnerComp, MemoryBlock, Op, OtherIntValue, OtherFloatValue);
}

bool UPZ_SkillTreeBlackboardKeyType::TestArithmeticOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeArithmeticKeyOperation::Type Op, int32 OtherIntValue, float OtherFloatValue) const
{
	return false;
}

bool UPZ_SkillTreeBlackboardKeyType::WrappedTestTextOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeTextKeyOperation::Type Op, const FString& OtherString) const
{
	if (HasInstance())
	{
		const UPZ_SkillTreeBlackboardKeyType* InstancedKey = GetKeyInstance(OwnerComp, MemoryBlock);
		const uint8* InstanceMemoryBlock = MemoryBlock + sizeof(FBlackboardInstancedKeyMemory);
		return InstancedKey->TestTextOperation(OwnerComp, InstanceMemoryBlock, Op, OtherString);
	}

	return TestTextOperation(OwnerComp, MemoryBlock, Op, OtherString);
}

bool UPZ_SkillTreeBlackboardKeyType::TestTextOperation(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock, ESkillTreeTextKeyOperation::Type Op, const FString& OtherString) const
{
	return false;
}

FString UPZ_SkillTreeBlackboardKeyType::WrappedDescribeValue(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock) const
{
	if (HasInstance())
	{
		const UPZ_SkillTreeBlackboardKeyType* InstancedKey = GetKeyInstance(OwnerComp, MemoryBlock);
		const uint8* InstanceMemoryBlock = MemoryBlock + sizeof(FBlackboardInstancedKeyMemory);
		return InstancedKey->DescribeValue(OwnerComp, InstanceMemoryBlock);
	}

	return DescribeValue(OwnerComp, MemoryBlock);
}

FString UPZ_SkillTreeBlackboardKeyType::DescribeValue(const UPZ_SkillTreeContext& OwnerComp, const uint8* RawData) const
{
	FString DescBytes;
	for (int32 ValueIndex = 0; ValueIndex < ValueSize; ValueIndex++)
	{
		DescBytes += FString::Printf(TEXT("%X"), RawData[ValueIndex]);
	}

	return DescBytes.Len() ? (FString("0x") + DescBytes) : FString("empty");
}

ESkillTreeBlackboardCompare::Type UPZ_SkillTreeBlackboardKeyType::CompareValues(const UPZ_SkillTreeContext& OwnerComp, const uint8* MemoryBlock,
	const UPZ_SkillTreeBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const
{
	const int32 MemCmp = FMemory::Memcmp(MemoryBlock, OtherMemoryBlock, GetValueSize());
	return MemCmp ? ESkillTreeBlackboardCompare::NotEqual : ESkillTreeBlackboardCompare::Equal;
}

void UPZ_SkillTreeBlackboardKeyType::CopyValues(UPZ_SkillTreeContext& OwnerComp, uint8* MemoryBlock, const UPZ_SkillTreeBlackboardKeyType* SourceKeyOb, const uint8* SourceBlock)
{
	FMemory::Memcpy(MemoryBlock, SourceBlock, GetValueSize());
}

bool UPZ_SkillTreeBlackboardKeyType::IsAllowedByFilter(UPZ_SkillTreeBlackboardKeyType* FilterOb) const
{
	return GetClass() == (FilterOb ? FilterOb->GetClass() : NULL);
}

FString UPZ_SkillTreeBlackboardKeyType::DescribeSelf() const
{
	return FString();
}

FString UPZ_SkillTreeBlackboardKeyType::DescribeArithmeticParam(int32 IntValue, float FloatValue) const
{
	return FString();
}

//----------------------------------------------------------------------//
// DEPRECATED
//----------------------------------------------------------------------//
UPZ_SkillTreeBlackboardKeyType* UPZ_SkillTreeBlackboardKeyType::UpdateDeprecatedKey()
{
	return nullptr;
}
