#pragma once

#include "interface/ICommand.hh"
#include <any>
#include <vector>

class ACommand : public ICommand
{
  public:
    ACommand(
        ICommandType type_,
        Callback callback_) : ICommand(type_, std::move(callback_)) {}
    virtual void execute() = 0;
    ~ACommand() override = default;

    std::vector<std::any> args;
    void addArgument(std::any arg) { args.push_back(std::move(arg)); };
};
