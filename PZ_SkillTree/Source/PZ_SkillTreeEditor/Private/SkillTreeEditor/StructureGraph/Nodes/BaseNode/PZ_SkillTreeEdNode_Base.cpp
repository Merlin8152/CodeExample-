// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeEditor/StructureGraph/Nodes/BaseNode/PZ_SkillTreeEdNode_Base.h"

#include "PZ_SkillTreeSNode_Base.h"

#include "../../Graph/PZ_SkillTreeStructureEdGraph.h"
#include "PZ_SkillTree_Editor.h"

#include "../../../PZ_SkillTreeEditorStyle.h"

#include "SkillTreeEditor/PZ_SkillTreeEditorConstant.h"
#include "Nodes/BaseNode/PZ_SkillTreeRBaseNode.h"
#include "Nodes/UINode/PZ_SkillTreeRUINode.h"

#include "SkillTreeEditor/StructureGraph/Nodes/EdgePoint/PZ_SkillTreeEdNode_Edge.h"

#define LOCTEXT_NAMESPACE "SkillTreeEditor"

UPZ_SkillTreeEdNode_Base::UPZ_SkillTreeEdNode_Base()
{
	bCanRenameNode = false;

}




void UPZ_SkillTreeEdNode_Base::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, FPZ_SkillTreeEditorConstant::PinCategory_Main, FPZ_SkillTreeEditorConstant::PinSubCategory_TopBottom, TEXT("In"));
	CreatePin(EGPD_Output, FPZ_SkillTreeEditorConstant::PinCategory_Main, FPZ_SkillTreeEditorConstant::PinSubCategory_TopBottom, TEXT("Out"));

}


void UPZ_SkillTreeEdNode_Base::PrepareForCopying()
{
	Super::PrepareForCopying();

	RNode->Rename(nullptr, this, REN_DontCreateRedirectors | REN_DoNotDirty);

}


void UPZ_SkillTreeEdNode_Base::AutowireNewNode(UEdGraphPin* FromPin)
{
	Super::AutowireNewNode(FromPin);

	if (FromPin)
	{
		if (GetSchema()->TryCreateConnection(FromPin, GetInputPin(FromPin->PinType.PinCategory)))
		{
			FromPin->GetOwningNode()->NodeConnectionListChanged();
		}
	}
}







bool UPZ_SkillTreeEdNode_Base::IsHaveUINode() const
{
	return false;
}

bool UPZ_SkillTreeEdNode_Base::CanDuplicateNode() const
{
	return true;
}

bool UPZ_SkillTreeEdNode_Base::CanUserDeleteNode() const
{
	return true;
}

bool UPZ_SkillTreeEdNode_Base::CanSplitPin(const UEdGraphPin* Pin) const
{
	return false;
}

bool UPZ_SkillTreeEdNode_Base::CanCreateUnderSpecifiedSchema(const UEdGraphSchema* Schema) const
{
	return true;
}








ESkillTreeNodeType UPZ_SkillTreeEdNode_Base::GetNodeType() const
{
	return ESkillTreeNodeType::None;
}



UEdGraphPin* UPZ_SkillTreeEdNode_Base::GetInputPin(const FName& PinCategory) const
{
	for (UEdGraphPin* Pin : Pins)
	{
		if (Pin->Direction == EEdGraphPinDirection::EGPD_Input && Pin->PinType.PinCategory == PinCategory)
		{
			return Pin;
		}
	}
	
	return nullptr;
}


UEdGraphPin* UPZ_SkillTreeEdNode_Base::GetOutputPin(const FName& PinCategory) const
{
	for (UEdGraphPin* Pin : Pins)
	{
		if (Pin->Direction == EEdGraphPinDirection::EGPD_Output && Pin->PinType.PinCategory == PinCategory)
		{
			return Pin;
		}
	}

	return nullptr;
}






void UPZ_SkillTreeEdNode_Base::CompileThisNodeInfo(UPZ_SkillTree_Editor* SkillTree)
{

	CompileError(SkillTree);

	if (SkillTree)
	{

		int32 NodeIndex = SkillTree->CompiledNodes.Add(RNode);

		if (RNode)
		{
			RNode->ResetNavigationNode();
			RNode->MyIndex = NodeIndex;
			RNode->NodeType = GetNodeType();
			RNode->Rename(nullptr, SkillTree, REN_DontCreateRedirectors | REN_DoNotDirty);//теперь хранится в SkillTreeEditor, из-за чего не очищается во время компиляции

			// не уверен что созданию UI ноды тут место, но да пусть
			if (IsHaveUINode())
			{
				if (!RNode->UINode)
				{
					RNode->UINode = NewObject<UPZ_SkillTreeRUINode>(RNode);
					if (RNode->UINode)	RNode->UINode->RNodeLink = RNode;
				}
			}
			else
			{
				RNode->UINode = nullptr;
			}
		}


		//////////////////////////// UI Graph ////////////////////////////
		if (UPZ_SkillTreeRBaseNode* CompiledRBaseNode = Cast<UPZ_SkillTreeRBaseNode>(RNode))
		{
			UPZ_SkillTreeRUINode* UINode = CompiledRBaseNode->UINode;
			if (IsValid(UINode))
			{
				if (CompiledRBaseNode != SkillTree->UIRoot)
				{
					UINode->IsUIRootNode = false;
					if (!UINode->IsPlacedInUI)
					{
						UINode->UIPosition.Set(CompiledRBaseNode->TempUIPositionOnCompile.X - SkillTree->UIRoot->TempUIPositionOnCompile.X,
							CompiledRBaseNode->TempUIPositionOnCompile.Y - SkillTree->UIRoot->TempUIPositionOnCompile.Y);
						UINode->IsPlacedInUI = true;
					}
				}
				else
				{
					UINode->IsUIRootNode = true;
					UINode->UIPosition.Set(0.f, 0.f);
					UINode->IsPlacedInUI = false;
				}
			}

		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
}


















bool UPZ_SkillTreeEdNode_Base::CanCreateConnectionTo(const UPZ_SkillTreeEdNode_Base* ToNode, FText& ErrorMessage, bool& CreateEdge) const
{
	CreateEdge = true;
	return true;
}


bool UPZ_SkillTreeEdNode_Base::IsNeedCompile()
{
	UEdGraphPin* InMainPin = GetInputPin(FPZ_SkillTreeEditorConstant::PinCategory_Main);

	if (InMainPin && InMainPin->LinkedTo.Num() > 0)
	{
		bool IsHaveCompiledPrevNode = false;
		for (const auto& LinkedToPin : InMainPin->LinkedTo)
		{
			if (IPZ_SkillTreeNodeInterface* LSkillTreeeNode = Cast<IPZ_SkillTreeNodeInterface>(LinkedToPin->GetOwningNode()))
			{
				if (LSkillTreeeNode->IsNeedCompile())
				{
					IsHaveCompiledPrevNode = true;
					break;
				}
			}
		}
		return IsHaveCompiledPrevNode;
	}
	return true;
}

void UPZ_SkillTreeEdNode_Base::OnNodeDoubleClicked()
{
	// TODO on childs
}


void UPZ_SkillTreeEdNode_Base::OnChangedProperties(const FName& PropertyName) const
{
	SEdNode->UpdateGraphNode();
	this->StaticClass();
}












bool UPZ_SkillTreeEdNode_Base::HasOutputConnectionToNode(const UEdGraphNode* TargetNode) const
{
	// проверяем все пины ищем Out
	for (UEdGraphPin* Pin : Pins)
	{
		if (Pin->Direction == EEdGraphPinDirection::EGPD_Output)
		{
			for (UEdGraphPin* ChildInputPin : Pin->LinkedTo)
			{
				UPZ_SkillTreeEdNode_Edge* EdgeNode = Cast<UPZ_SkillTreeEdNode_Edge>(ChildInputPin->GetOwningNode());

				//если соединение через Edge, его не учитываем
				if (EdgeNode)
				{
					if (EdgeNode->GetEndNode() == TargetNode)
					{
						return true;
					}
				}//эсли соединение без посредников - проверяем напрямую
				else if (ChildInputPin->GetOwningNode() == TargetNode)
				{
					return true;
				}
			}
		}
	}

	return false;
}



bool UPZ_SkillTreeEdNode_Base::CanContainsSubNode(UClass* SubNodeClass)
{
	return false;
}

void UPZ_SkillTreeEdNode_Base::SetPosition(int32 X, int32 Y)
{
	NodePosX = X;
	NodePosY = Y;
}



bool UPZ_SkillTreeEdNode_Base::AddSubNode(UPZ_SkillTreeEdNode_Base* SubNode, class UEdGraph* ParentGraph)
{
	if (!CanContainsSubNode(SubNode->GetClass())) return false;

	const FScopedTransaction Transaction(LOCTEXT("AddNode", "Add Node"));
	ParentGraph->Modify();
	Modify();

	SubNode->SetFlags(RF_Transactional);

	// set outer to be the graph so it doesn't go away
	SubNode->Rename(nullptr, ParentGraph, REN_NonTransactional);
	SubNode->ParentNode = this;


	SubNode->CreateNewGuid();
	SubNode->PostPlacedNewNode();
	SubNode->AllocateDefaultPins();
	SubNode->AutowireNewNode(nullptr);

	SubNode->NodePosX = 0;
	SubNode->NodePosY = 0;

	SubNodes.Add(SubNode);
	OnSubNodeAdded(SubNode);


	ParentGraph->NotifyGraphChanged();

	return true;
}

void UPZ_SkillTreeEdNode_Base::RemoveSubNode(UPZ_SkillTreeEdNode_Base* SubNode)
{
	SubNodes.RemoveSingle(SubNode);
	Modify();

	OnSubNodeRemoved(SubNode);
}

void UPZ_SkillTreeEdNode_Base::RemoveAllSubNodes()
{
	SubNodes.Reset();
}

void UPZ_SkillTreeEdNode_Base::OnSubNodeRemoved(UPZ_SkillTreeEdNode_Base* SubNode)
{
	//override
}

void UPZ_SkillTreeEdNode_Base::OnSubNodeAdded(UPZ_SkillTreeEdNode_Base* SubNode)
{
	//override
}


void UPZ_SkillTreeEdNode_Base::DestroyNode()
{
	if (ParentNode)
	{
		ParentNode->RemoveSubNode(this);
	}

	Super::DestroyNode();
}

bool UPZ_SkillTreeEdNode_Base::IsHaveInConnection(const FName& PinCategory)
{
	int InConnectionCount = 0;
	if (UEdGraphPin* InPin = GetInputPin(PinCategory))
	{
		InConnectionCount += InPin->LinkedTo.Num();
	}

	return InConnectionCount > 0 ? true : false;
}

bool UPZ_SkillTreeEdNode_Base::IsHaveOutConnection(const FName& PinCategory)
{
	int OutConnectionCount = 0;
	if (UEdGraphPin* OutPin = GetOutputPin(PinCategory))
	{
		OutConnectionCount += OutPin->LinkedTo.Num();
	}

	return OutConnectionCount > 0 ? true : false;
}


bool UPZ_SkillTreeEdNode_Base::IsSubNode() const
{
	return ParentNode != nullptr;
}

