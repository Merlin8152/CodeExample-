// Fill out your copyright notice in the Description page of Project Settings.


#include "PZ_SkillTreeContext.h"


#include "PZ_SkillTree_Editor.h"

#include "PZ_SkillTreeRNodesInclude.h"
#include "SkillTreeEvent/PZ_SkillTreeEvent.h"
#include "SkillTreeEvent/PZ_SkillTreeCondition.h"
#include "SkillTreeComponent/PZ_SkillTreeComponent.h"


/////////////////////// BlackBoard include ///////////////////////////////////

#include "SkillTreeBlackBoard/PZ_SkillTreeBlackboardKeyType.h"


#include "SkillTreeBlackBoard/BlackBoardType/PZ_SkillTreeBlackboardTypeRotate.h"
#include "SkillTreeBlackBoard/BlackBoardType/PZ_SkillTreeBlackboardType_Enum.h"
#include "SkillTreeBlackBoard/BlackBoardType/PZ_SkillTreeBlackboardType_Name.h"
#include "SkillTreeBlackBoard/BlackBoardType/PZ_SkillTreeBlackboardTypeString.h"
#include "SkillTreeBlackBoard/BlackBoardType/PZ_SkillTreeBlackboardType_class.h"
#include "SkillTreeBlackBoard/BlackBoardType/PZ_SkillTreeBlackboardType_Int.h"
#include "SkillTreeBlackBoard/BlackBoardType/PZ_SkillTreeBlackboardType_float.h"
#include "SkillTreeBlackBoard/BlackBoardType/PZ_SkillTreeBlackboardTypeVector.h"
#include "SkillTreeBlackBoard/BlackBoardType/PZ_SkillTreeBlackboardTypeObject.h"
#include "SkillTreeBlackBoard/BlackBoardType/PZ_SkillTreeBlackboardType_bool.h"

//////////////////////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////////// Initialize methods ///////////////////////////////////////////////


UPZ_SkillTreeContext::UPZ_SkillTreeContext(UPZ_SkillTree_Editor* SkillTree, AActor* PlayerCharacter, UPZ_SkillTreeComponent* InSTComponent)
{
	InitContext(SkillTree, PlayerCharacter, InSTComponent);
}



void UPZ_SkillTreeContext::InitContext(UPZ_SkillTree_Editor* SkillTree, AActor* PlayerCharacter, UPZ_SkillTreeComponent* InSTComponent)
{
	ImplementSkillTree = SkillTree;
	Player = PlayerCharacter;
	STComponent = InSTComponent;

	if (SkillTree->SkillTreeBlackBoard.Num() > 0) 
	{
		BlackBoardValues = SkillTree->SkillTreeBlackBoard;

		InitializeBlackboard();
	}



	TArray<UPZ_SkillTreeRBaseTreeElement*> RootNodes;
	SkillTree->GetRootNodes(RootNodes);

	TArray<UPZ_SkillTreeRBaseTreeElement*> CreatedNodes;
	for (const auto& LRootNode : RootNodes)
	{
		CreateAndLinkContextNodes(CreatedNodes, LRootNode);
	}

}

void UPZ_SkillTreeContext::CreateAndLinkContextNodes(TArray<UPZ_SkillTreeRBaseTreeElement*>& CreatedNodes, UPZ_SkillTreeRBaseTreeElement* RootNode, UPZ_SkillTreeContextItem_Base* ParentContext)
{
	if (CreatedNodes.Contains(RootNode)) return;
	UPZ_SkillTreeContextItem_Base* ContextItem = RootNode->CreateContext(this);
	UPZ_SkillTreeContextItem_Base* LParentContext = ParentContext;
	if (ContextItem)
	{
		ContextItem->SkillTreeContext = this;
		ContextNodeInfo2.Add(RootNode->MyIndex, ContextItem);
		
		if (ParentContext)
		{
			LParentContext->NextContextNodes.Add(ContextItem);
			ContextItem->ParentContextNodes.Add(LParentContext);
		}
		LParentContext = ContextItem;
	}

	CreatedNodes.Add(RootNode);


	TArray<UPZ_SkillTreeRBaseTreeElement*> NextContextNodes;
	RootNode->GetOutRNodesByClass_WithContext<UPZ_SkillTreeRBaseTreeElement>(NextContextNodes);
	for (const auto& LNextNode : NextContextNodes)
	{
		CreateAndLinkContextNodes(CreatedNodes, LNextNode, LParentContext);
	}
}

bool UPZ_SkillTreeContext::InitializeBlackboard()
{
	

	ValueMemory.Reset();
	ValueOffsets.Reset();

	bool bSuccess = true;

	

	TArray<FBlackboardInitializationData> InitList;
	const int32 NumKeys = BlackBoardValues.Num();//BlackboardAsset->GetNumKeys();

	InitList.Reserve(NumKeys);
	ValueOffsets.AddZeroed(NumKeys);

		
	for (int32 KeyIndex = 0; KeyIndex < BlackBoardValues.Num(); KeyIndex++)
	{
		UPZ_SkillTreeBlackboardKeyType* KeyType = BlackBoardValues[KeyIndex].KeyType;//It->Keys[KeyIndex].KeyType;
		if (KeyType)
		{

			KeyType->PreInitialize(*this);

			const uint16 KeyMemory = KeyType->GetValueSize() + (KeyType->HasInstance() ? sizeof(FBlackboardInstancedKeyMemory) : 0);
			InitList.Add(FBlackboardInitializationData(KeyIndex, KeyMemory));
		}
	}
		

	// sort key values by memory size, so they can be packed better
	// it still won't protect against structures, that are internally misaligned (-> uint8, uint32)
	// but since all Engine level keys are good... 
	InitList.Sort(FBlackboardInitializationData::FMemorySort());
	uint16 MemoryOffset = 0;
	for (int32 Index = 0; Index < InitList.Num(); Index++)
	{
		ValueOffsets[InitList[Index].KeyID] = MemoryOffset;
		MemoryOffset += InitList[Index].DataSize;
	}

	ValueMemory.AddZeroed(MemoryOffset);

	// initialize memory
	KeyInstances.AddZeroed(InitList.Num());
	for (int32 Index = 0; Index < InitList.Num(); Index++)
	{
		const FSkillTreeBlackboardEntry* KeyData = &BlackBoardValues[InitList[Index].KeyID];//BlackboardAsset->GetKey(InitList[Index].KeyID);


		KeyData->KeyType->InitializeKey(*this, InitList[Index].KeyID);
	}

	return bSuccess;


}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void UPZ_SkillTreeContext::BeginDestroy()
{
	Super::BeginDestroy();

	DestroyValues();
}






/////////////////////////////////////////////// Get Set  methods ///////////////////////////////////////////////




UPZ_SkillTree_Editor* UPZ_SkillTreeContext::GetImplementedSkillTree() const
{
	return ImplementSkillTree;
}



void UPZ_SkillTreeContext::GetNextNodesToUpdate(UPZ_SkillTreeRBaseTreeElement* AnchorNode, TArray<UPZ_SkillTreeRBaseTreeElement*>& NextNodesArray)
{
	TArray<UPZ_SkillTreeRBaseTreeElement*> NextNodes;
	AnchorNode->GetOutRNodesByClass<UPZ_SkillTreeRBaseTreeElement>(NextNodes);

	for (const auto& NextNode : NextNodes)
	{
		//if (NextNode->IsA(UPZ_SkillTreeRSkillNode::StaticClass)  ||
		//	NextNode->IsA(UPZ_SkillTreeRConnectionNode::StaticClass))
		if (NextNode->IsA(UPZ_SkillTreeRSkillNode::StaticClass())  ||
			NextNode->IsA(UPZ_SkillTreeRConnectionNode::StaticClass()))
		{
			NextNodesArray.AddUnique(NextNode);
		}
		else
		{
			GetNextNodesToUpdate(NextNode, NextNodesArray);
		}
	}


}

void UPZ_SkillTreeContext::GetPrevNodesToUpdate(UPZ_SkillTreeRBaseTreeElement* AnchorNode, TArray<UPZ_SkillTreeRBaseTreeElement*>& PrevNodesArray)
{
	TArray<UPZ_SkillTreeRBaseTreeElement*> PrevNodes;
	AnchorNode->GetInRNodesByClass<UPZ_SkillTreeRBaseTreeElement>(PrevNodes);

	for (const auto& PrevNode : PrevNodes)
	{
		if (PrevNode->IsA(UPZ_SkillTreeRSwitcherNode::StaticClass()) ||
			PrevNode->IsA(UPZ_SkillTreeRConnectionNode::StaticClass()))
		{
			PrevNodesArray.AddUnique(PrevNode);
		}
		else
		{
			GetPrevNodesToUpdate(PrevNode, PrevNodesArray);
		}
	}
}

bool UPZ_SkillTreeContext::IsHavePrevSkillNode(UPZ_SkillTreeRSkillNode* InSkillNode)
{
	TArray<UPZ_SkillTreeRSkillNode*> PrevSkillNodes;
	InSkillNode->GetInRNodesByClass<UPZ_SkillTreeRSkillNode>(PrevSkillNodes);
	return PrevSkillNodes.Num() > 0;
}



TArray<UPZ_SkillTreeRBaseTreeElement*> UPZ_SkillTreeContext::GetNextNodes(UPZ_SkillTreeRBaseTreeElement* AnchorNode)
{
	TArray<UPZ_SkillTreeRBaseTreeElement*> NextNodes;

	for (auto Node : AnchorNode->NextNodes)
	{
		if (UPZ_SkillTreeREdgeNode* LEdgePoint = Cast<UPZ_SkillTreeREdgeNode>(Node))
		{
			for (auto NextNode : LEdgePoint->NextNodes)
			{
				NextNodes.Add(NextNode);
			}
		}
	}

	return NextNodes;
}







TArray<UPZ_SkillTreeRBaseTreeElement*> UPZ_SkillTreeContext::GetPreviousNodes(UPZ_SkillTreeRBaseTreeElement* AnchorNode)
{
	TArray<UPZ_SkillTreeRBaseTreeElement*> PreviousNodes;

	for (auto Node : AnchorNode->ParentNodes)
	{
		if (UPZ_SkillTreeREdgeNode* LEdgePoint = Cast<UPZ_SkillTreeREdgeNode>(Node))
		{
			for (auto PreviousNode : LEdgePoint->ParentNodes)
			{
				PreviousNodes.Add(PreviousNode);
			}
		}
	}

	return PreviousNodes;
}







FVector2D UPZ_SkillTreeContext::GetNodeUILocationByIndex(int NodeIndex)
{
	//реальзация неактуальна, ui теперь не тольно у скилов (Переделать)
	if (ImplementSkillTree->CompiledNodes.IsValidIndex(NodeIndex) && IsValid(ImplementSkillTree->CompiledNodes[NodeIndex]))
	{
		if (auto SkillNode = Cast<UPZ_SkillTreeRSkillNode>(ImplementSkillTree->CompiledNodes[NodeIndex]))
		{
			return SkillNode->UINode->UIPosition;
		}
	}

	return FVector2D();
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////










///////////////////////////// Execute For Nodes /////////////////////////////  




void UPZ_SkillTreeContext::ExecuteEvents(const TArray<UPZ_SkillTreeEvent*>& Events)
{

	for (const auto& LEvent : Events)
	{
		if (IsValid(LEvent)) 
		{
			LEvent->Execute(this, Player);

		}
	}
}



bool UPZ_SkillTreeContext::ExecuteCondition(const TArray<class UPZ_SkillTreeCondition*>& Conditions)
{
	bool CanExecute = true;


	if (Conditions.Num() == 0) return false;
	


	for (const auto& LCondition : Conditions)
	{

		if (!IsValid(LCondition) || !CanExecute) return false;


		CanExecute = LCondition->Execute(this, Player);


	}

	return CanExecute;
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////









/////////////////////////////////////////////// Checks  methods ///////////////////////////////////////////////



bool UPZ_SkillTreeContext::CanExecuteEvent(UPZ_SkillTreeREventNode* EventNode)
{

	for (auto EventSubNode : EventNode->NextNodes)
	{

		if (auto SkillNode = Cast<UPZ_SkillTreeRSkillNode>(EventSubNode))
		{
			if (UPZ_SkillTreeContextItem_Skill* SkillContext = Cast<UPZ_SkillTreeContextItem_Skill>(ContextNodeInfo2[SkillNode->MyIndex]))
			{
				if (!CanExecuteSkillNode(SkillNode, SkillContext->CurrentSkillLayer)) return false;
			}

		}	

	}

	return true;
}




bool UPZ_SkillTreeContext::CanExecuteEventByName(const FName& EventName)
{

	auto CurrentEvent = ImplementSkillTree->CompiledEventNodes[EventName];


	return CanExecuteEvent(CurrentEvent);

}





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////////// Execute  methods ///////////////////////////////////////////////


void UPZ_SkillTreeContext::ExecuteNode(UPZ_SkillTreeRBaseTreeElement* SkillNode)
{
	ContextNodeInfo2[SkillNode->MyIndex]->OnExecute();
}



bool UPZ_SkillTreeContext::ExecudeEventNode(FName EventNodeName)
{

	if (ImplementSkillTree->CompiledEventNodes.Contains(EventNodeName))
	{
		auto EventNode = ImplementSkillTree->CompiledEventNodes[EventNodeName];


		if (!CanExecuteEvent(EventNode)) return false; 
		

		for (auto EventSubNode : EventNode->NextNodes)
		{
			ExecuteNode(EventSubNode);
		}

		return true;

	}

	return false;

}

bool UPZ_SkillTreeContext::CanExecuteSkillNode(UPZ_SkillTreeRSkillNode* InSkillNode, int Layer)
{
	if (!IsValid(InSkillNode)) return false;

	if( InSkillNode->Layers.Num() && IsValid(InSkillNode->Layers[Layer]->ConditionNode) )
	{
		if (auto Condition = Cast<UPZ_SkillTreeRConditionNode>(InSkillNode->Layers[Layer]->ConditionNode))
		{
			bool IsOpen = false;
			bool CanBeOpen = false;		
			UPZ_SkillTreeContextItem_Skill* SkillContext = Cast<UPZ_SkillTreeContextItem_Skill>(ContextNodeInfo2[InSkillNode->MyIndex]);
			if (SkillContext)
			{
				IsOpen = SkillContext->IsOpen;
				CanBeOpen = SkillContext->CanBeOpen;			
			}

			if (!Condition->OnExecute(this) || IsOpen || (!CanBeOpen && (!InSkillNode->AlwaysCanBeOpen && /*!InSkillNode->IsRootNode &&*/ IsHavePrevSkillNode(InSkillNode)))) return false;
		}
	}
	else
	{
		bool IsOpen = false;
		bool CanBeOpen = false;
		UPZ_SkillTreeContextItem_Skill* SkillContext = Cast<UPZ_SkillTreeContextItem_Skill>(ContextNodeInfo2[InSkillNode->MyIndex]);
		if (SkillContext)
		{
			IsOpen = SkillContext->IsOpen;
			CanBeOpen = SkillContext->CanBeOpen;
		}

		if (IsOpen || (!CanBeOpen && (!InSkillNode->AlwaysCanBeOpen && /*!InSkillNode->IsRootNode &&*/ IsHavePrevSkillNode(InSkillNode)))) return false;
	}

	return true;
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


















/////////////////////////////////////////////// BlackBoard methods ///////////////////////////////////////////////



template<class TDataClass>
bool UPZ_SkillTreeContext::SetValue(const FName& KeyName, typename TDataClass::FDataType Value)
{
	const FBlackboard::FKey KeyID = GetKeyID(KeyName);
	return SetValue<TDataClass>(KeyID, Value);
}

template<class TDataClass>
bool UPZ_SkillTreeContext::SetValue(FBlackboard::FKey KeyID, typename TDataClass::FDataType Value)
{

	 FSkillTreeBlackboardEntry *EntryInfo =  &BlackBoardValues[KeyID];

	if (EntryInfo == nullptr || EntryInfo->KeyType == nullptr || EntryInfo->KeyType->GetClass() != TDataClass::StaticClass())
	{

		return false;
	}
	

	const uint16 DataOffset = EntryInfo->KeyType->HasInstance() ? sizeof(FBlackboardInstancedKeyMemory) : 0;
	uint8* RawData = GetKeyRawData(KeyID) + DataOffset;
	if (RawData)
	{

		UPZ_SkillTreeBlackboardKeyType* KeyOb = EntryInfo->KeyType->HasInstance() ? KeyInstances[KeyID] : EntryInfo->KeyType;
		TDataClass::SetValue((TDataClass*)KeyOb, RawData, Value);
	
		return true;
	}

	return false;
}

template<class TDataClass>
typename TDataClass::FDataType UPZ_SkillTreeContext::GetValue(const FName& KeyName) const
{
	const FBlackboard::FKey KeyID = GetKeyID(KeyName);
	return GetValue<TDataClass>(KeyID);
}

template<class TDataClass>
typename TDataClass::FDataType UPZ_SkillTreeContext::GetValue(FBlackboard::FKey KeyID) const
{
	const FSkillTreeBlackboardEntry* EntryInfo = &BlackBoardValues[KeyID];

	if ((EntryInfo == nullptr) || (EntryInfo->KeyType == nullptr) || (EntryInfo->KeyType->GetClass() != TDataClass::StaticClass()))
	{
		return TDataClass::InvalidValue;
	}

	UPZ_SkillTreeBlackboardKeyType* KeyOb = EntryInfo->KeyType->HasInstance() ? KeyInstances[KeyID] : EntryInfo->KeyType;
	const uint16 DataOffset = EntryInfo->KeyType->HasInstance() ? sizeof(FBlackboardInstancedKeyMemory) : 0;
	const uint8* RawData = GetKeyRawData(KeyID) + DataOffset;

	return RawData ? TDataClass::GetValue((TDataClass*)KeyOb, RawData) : TDataClass::InvalidValue;
}



void UPZ_SkillTreeContext::OnContextExecuteProcedure(UPZ_SkillTreeContextItem_Base* InContextItem)
{
	OnContextExecute.Broadcast(InContextItem->SkillTreeNode->MyIndex);
}

void UPZ_SkillTreeContext::OnContextUpdateProcedure(UPZ_SkillTreeContextItem_Base* InContextItem)
{
	OnContextUpdate.Broadcast(InContextItem->SkillTreeNode->MyIndex);
}

FBlackboard::FKey UPZ_SkillTreeContext::GetKeyID(const FName& KeyName) const
{
	for (int32 KeyIndex = 0; KeyIndex < BlackBoardValues.Num(); KeyIndex++)
	{
		if (BlackBoardValues[KeyIndex].EntryName == KeyName)
		{
			return KeyIndex;
		}
	}

	return FBlackboard::InvalidKey;
}



UObject* UPZ_SkillTreeContext::GetValueAsObject(const FName& KeyName) const
{
	return GetValue<UPZ_SkillTreeBlackboardTypeObject>(KeyName);
}

UClass* UPZ_SkillTreeContext::GetValueAsClass(const FName& KeyName) const
{
	return GetValue<UPZ_SkillTreeBlackboardType_class>(KeyName);
}

uint8 UPZ_SkillTreeContext::GetValueAsEnum(const FName& KeyName) const
{
	return GetValue<UPZ_SkillTreeBlackboardType_Enum>(KeyName);
}

int32 UPZ_SkillTreeContext::GetValueAsInt(const FName& KeyName) const
{
	return GetValue<UPZ_SkillTreeBlackboardType_Int>(KeyName);
}

float UPZ_SkillTreeContext::GetValueAsFloat(const FName& KeyName) const
{
	return GetValue<UPZ_SkillTreeBlackboardType_float>(KeyName);
}

bool UPZ_SkillTreeContext::GetValueAsBool(const FName& KeyName) const
{
	return GetValue<UPZ_SkillTreeBlackboardType_bool>(KeyName);
}

FString UPZ_SkillTreeContext::GetValueAsString(const FName& KeyName) const
{
	return GetValue<UPZ_SkillTreeBlackboardTypeString>(KeyName);
}

FName UPZ_SkillTreeContext::GetValueAsName(const FName& KeyName) const
{
	return GetValue<UPZ_SkillTreeBlackboardType_Name>(KeyName);
}

FVector UPZ_SkillTreeContext::GetValueAsVector(const FName& KeyName) const
{
	return GetValue<UPZ_SkillTreeBlackboardTypeVector>(KeyName);
}

FRotator UPZ_SkillTreeContext::GetValueAsRotator(const FName& KeyName) const
{
	return GetValue<UPZ_SkillTreeBlackboardTypeRotate>(KeyName);
}

void UPZ_SkillTreeContext::SetValueAsObject(const FName& KeyName, UObject* ObjectValue)
{
	const FBlackboard::FKey KeyID = GetKeyID(KeyName);
	SetValue<UPZ_SkillTreeBlackboardTypeObject>(KeyID, ObjectValue);
}

void UPZ_SkillTreeContext::SetValueAsClass(const FName& KeyName, UClass* ClassValue)
{
	const FBlackboard::FKey KeyID = GetKeyID(KeyName);
	SetValue<UPZ_SkillTreeBlackboardType_class>(KeyID, ClassValue);
}

void UPZ_SkillTreeContext::SetValueAsEnum(const FName& KeyName, uint8 EnumValue)
{
	const FBlackboard::FKey KeyID = GetKeyID(KeyName);
	SetValue<UPZ_SkillTreeBlackboardType_Enum>(KeyID, EnumValue);
}

void UPZ_SkillTreeContext::SetValueAsInt(const FName& KeyName, int32 IntValue)
{
	const FBlackboard::FKey KeyID = GetKeyID(KeyName);
	SetValue<UPZ_SkillTreeBlackboardType_Int>(KeyID, IntValue);
}

void UPZ_SkillTreeContext::SetValueAsFloat(const FName& KeyName, float FloatValue)
{
	const FBlackboard::FKey KeyID = GetKeyID(KeyName);
	SetValue<UPZ_SkillTreeBlackboardType_float>(KeyID, FloatValue);
}

void UPZ_SkillTreeContext::SetValueAsBool(const FName& KeyName, bool BoolValue)
{
	const FBlackboard::FKey KeyID = GetKeyID(KeyName);
	SetValue<UPZ_SkillTreeBlackboardType_bool>(KeyID, BoolValue);
}

void UPZ_SkillTreeContext::SetValueAsString(const FName& KeyName, FString StringValue)
{
	const FBlackboard::FKey KeyID = GetKeyID(KeyName);
	SetValue<UPZ_SkillTreeBlackboardTypeString>(KeyID, StringValue);
}

void UPZ_SkillTreeContext::SetValueAsName(const FName& KeyName, FName NameValue)
{
	const FBlackboard::FKey KeyID = GetKeyID(KeyName);
	SetValue<UPZ_SkillTreeBlackboardType_Name>(KeyID, NameValue);
}

void UPZ_SkillTreeContext::SetValueAsVector(const FName& KeyName, FVector VectorValue)
{
	const FBlackboard::FKey KeyID = GetKeyID(KeyName);
	SetValue<UPZ_SkillTreeBlackboardTypeVector>(KeyID, VectorValue);
}

void UPZ_SkillTreeContext::SetValueAsRotator(const FName& KeyName, FRotator RotatorValue)
{
	const FBlackboard::FKey KeyID = GetKeyID(KeyName);
	SetValue<UPZ_SkillTreeBlackboardTypeRotate>(KeyID, RotatorValue);
}


void UPZ_SkillTreeContext::DestroyValues()
{
	for (int32 KeyIndex = 0; KeyIndex < BlackBoardValues.Num(); KeyIndex++)
	{
		UPZ_SkillTreeBlackboardKeyType* KeyType = BlackBoardValues[KeyIndex].KeyType;
		if (KeyType)
		{
			const int32 UseIdx = KeyIndex;// + It->GetFirstKeyID();
			uint8* KeyMemory = GetKeyRawData(UseIdx);
			KeyType->WrappedFree(*this, KeyMemory);
		}		
	}

	BlackBoardValues.Empty();

	ValueOffsets.Reset();
	ValueMemory.Reset();

}