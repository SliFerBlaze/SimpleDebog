#include "backend/commands/ACommand.hh"
#include "backend/core/DebuggerEngine.hh"

class FakeCommand : public ACommand
{

  private:
    DebuggerEngine *_engine;

  public:
    explicit FakeCommand(DebuggerEngine *engine);
    ~FakeCommand();

    void execute() override;
};
