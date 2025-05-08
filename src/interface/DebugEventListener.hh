#pragma once

class DebugEventListener
{
  public:
    virtual ~DebugEventListener() = default;
    virtual void onEvent(const DebugEvent &event) = 0;
};
