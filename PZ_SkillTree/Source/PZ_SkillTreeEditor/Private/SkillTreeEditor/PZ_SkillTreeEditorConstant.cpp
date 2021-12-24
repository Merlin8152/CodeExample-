// Fill out your copyright notice in the Description page of Project Settings.


#include "PZ_SkillTreeEditorConstant.h"




//категория отвечает за соединение нод, на данный момент можно соеденить ноды только 1 категории
const FName FPZ_SkillTreeEditorConstant::PinCategory_Main("Main");
const FName FPZ_SkillTreeEditorConstant::PinCategory_Second("Second");

//подкатегория отвечает за визуальное отображение ноды (слева input справа output например)
const FName FPZ_SkillTreeEditorConstant::PinSubCategory_LeftRight("LeftRight");
const FName FPZ_SkillTreeEditorConstant::PinSubCategory_TopBottom("TopBottom");