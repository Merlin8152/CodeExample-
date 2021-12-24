// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"


class FPZ_SkillTreeEditorStyle
{


public:

	static void Initialize();
	static void Shutdown();

	static const FName& GetStyleSetName();
	static TSharedPtr<ISlateStyle> Get() { return StyleSet; }

	template< typename WidgetStyleType >
	static const WidgetStyleType& GetWidgetStyle(const FName& PropertyName, const ANSICHAR* Specifier = nullptr)
	{
		return StyleSet->GetWidgetStyle<WidgetStyleType>(PropertyName, Specifier);
	}



public:

	static const FName NodeIcon_DefaultIcon;
	static const FName NodeIcon_RootNodeIcon;
	static const FName NodeIcon_SkillNodeIcon;
	static const FName NodeIcon_ConditionNodeIcon;
	static const FName NodeIcon_SkillActionNodeIcon;
	static const FName NodeIcon_EventNodeIcon;
	static const FName NodeIcon_SwitchNodeIcon;
	static const FName NodeIcon_ConnectionNodeIcon;
	static const FName NodeIcon_CustomNodeIcon;

	static const FName NodeIcon_UINodeIcon;
private:

	static TSharedPtr<FSlateStyleSet> StyleSet;

};






