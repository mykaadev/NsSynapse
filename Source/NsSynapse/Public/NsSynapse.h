// Copyright (C) 2025 mykaadev. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/**
 * Ns Synapse Runtime Module
 */
class FNsSynapseModule : public IModuleInterface
{

// Functions
public:

    //~ Begin IModuleInterface Interface
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
    //~ End IModuleInterface Interface
};
