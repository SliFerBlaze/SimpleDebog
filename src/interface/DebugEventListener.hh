#pragma once

#include "interface/DebugEvent.hh"

class DebugEventListener
{
  public:
    virtual ~DebugEventListener() = default;
    virtual void onEvent(const DebugEvent &event) = 0;
};
