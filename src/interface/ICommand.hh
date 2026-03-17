#pragma once

#include <any>
#include <functional>
#include <memory>

enum class ICommandType {
    Fake, // For testing purposes
    Pause,
    Resume,
    Step,
    SaveState,
    LoadState,
};

using Callback = std::function<void(std::any)>;

class ICommand
{
  public:
    ICommand(
        ICommandType type_,
        Callback callback_) : type(type_),
                              callback(std::move(callback_)) {}
    virtual ~ICommand() = default;

    const ICommandType type;
    Callback callback;
};
