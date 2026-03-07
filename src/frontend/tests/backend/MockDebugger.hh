#pragma once
#include "../interface/IDebugger.hh"
#include "../interface/ICommand.hh"
#include <thread>
#include <chrono>
#include <mutex>

class MockDebugger : public IDebugger {
public:
    void addListener(DebugEventListener* listener) override {
        std::lock_guard<std::mutex> lock(mutex);
        listeners.push_back(listener);
    }

    void removeListener(DebugEventListener* listener) override {
        std::lock_guard<std::mutex> lock(mutex);
        listeners.erase(
            std::remove(listeners.begin(), listeners.end(), listener),
            listeners.end());
    }

    void executeCommand(std::unique_ptr<ICommand> cmd) override {
        // Simulate a small delay like a real debugger
        std::thread([this, c = std::move(cmd)]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            if (dynamic_cast<StepCommand*>(c.get())) {
                emitBreakpointEvent(0x401000 + rand() % 0x100);
                emitStackEvent();
            } else if (auto* addBp = dynamic_cast<AddBreakpointCommand*>(c.get())) {
                emitBreakpointEvent(addBp->address);
            }
        }).detach();
    }

private:
    std::vector<DebugEventListener*> listeners;
    std::mutex mutex;

    void emitBreakpointEvent(std::uintptr_t addr) {
        DebugEvent event{DebugEventType::BreakpointHit, addr, {}};
        notify(event);
    }

    void emitStackEvent() {
        std::vector<StackFrame> frames = {
            {"main()", 0x401000},
            {"foo()", 0x401050},
            {"bar()", 0x401080},
        };
        DebugEvent event{DebugEventType::StackUpdated, 0, frames};
        notify(event);
    }

    void notify(const DebugEvent& event) {
        std::lock_guard<std::mutex> lock(mutex);
        for (auto* l : listeners)
            l->onEvent(event);
    }
};
