﻿// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeExecutionContext.h"
#include "StateTreePropertyFunctionBase.h"
#include "Bach/Combo/Components/BachComboComponent.h"
#include "BachCheckComboWindowMatch.generated.h"

USTRUCT()
struct BACH_API FBachCheckComboWindowMatchInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = Parameter)
    TObjectPtr<UBachComboComponent> ComboComponent;

    UPROPERTY(EditAnywhere, Category = Parameter,
        meta=(Bitmask, BitmaskEnum="/Script/Bach.EBachComboWindowState"))

    int32 MatchState = 0;

    UPROPERTY(EditAnywhere, Category = Output)
    bool bMatched = false;
};


/**
 * 
 */
USTRUCT(DisplayName = "Match Combo Window")
struct BACH_API FBachCheckComboWindowMatch : public FStateTreePropertyFunctionCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FBachCheckComboWindowMatchInstanceData;

    virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

    virtual void Execute(FStateTreeExecutionContext& Context) const override
    {
        auto& [ComboComponent,MatchState,bMatched] = Context.GetInstanceData(*this);
        if (!ComboComponent)
        {
            return;
        }
        const auto CurrentState = ComboComponent->GetComboInfoSummary().ComboWindowState;
        bMatched = (static_cast<int32>(CurrentState) & MatchState) == static_cast<int>(CurrentState);
    };
};
