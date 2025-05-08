
#include "backend/core/DebuggerEngine.hh"
#include "backend/events/DebugEvent.hh"
#include "interface/DebugEventListener.hh"
#include "interface/IDebugger.hh"
#include "mocks/FakeCommand.hh"
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>

class MockDebugEventListener : public DebugEventListener
{
  public:
    void onEvent(const DebugEvent &event) override
    {
        std::cout << "MockDebugEventListener received event: " << event.description << std::endl;
    }
};

TEST(DebuggerEngineTest, InitialStateIsClean)
{
    DebuggerEngine engine;
    MockDebugEventListener listener;
    engine.addListener(&listener);
    engine.executeCommand(std::make_unique<FakeCommand>(&engine));
    auto command = engine.popCommand();
    ASSERT_NE(command, nullptr);

    std::stringstream coutBuffer;
    std::streambuf *oldCout = std::cout.rdbuf();
    std::cout.rdbuf(coutBuffer.rdbuf());
    std::string line;

    command->execute();

    std::cout.rdbuf(oldCout);

    getline(coutBuffer, line);
    EXPECT_EQ(line, "FakeCommand executed");

    getline(coutBuffer, line);
    EXPECT_EQ(line, "MockDebugEventListener received event: Fake command executed");
}
