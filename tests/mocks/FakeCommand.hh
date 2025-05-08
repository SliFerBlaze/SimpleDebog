#include "backend/commands/ICommand.hh"
#include "backend/core/DebuggerEngine.hh"

class FakeCommand : public ICommand
{

  private:
    DebuggerEngine *_engine;

  public:
    explicit FakeCommand(DebuggerEngine *engine);
    ~FakeCommand();

    void execute() override;
};
