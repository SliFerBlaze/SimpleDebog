#include "ILowLevelDebugger.hh"

std::map<pid_t, unsigned int> ILowLevelDebugger::_processes = {}; // Initialize the static member variable

ILowLevelDebugger::~ILowLevelDebugger()
{
    if (_pid <= 0) {
        return;
    }
    if (_processes.find(_pid) == _processes.end()) {
        return;
    }
    _processes[_pid]--;
    if (_processes[_pid] == 0) {
        detach();
    }
};

ILowLevelDebugger::ILowLevelDebugger(ILowLevelDebugger const &other)
{
    _processes[other._pid]++;
    _pid = other._pid;
};

ILowLevelDebugger::ILowLevelDebugger(ILowLevelDebugger &other)
{
    _processes[other._pid]++;
    _pid = other._pid;
};

void ILowLevelDebugger::detach()
{
    if (_pid <= 0) {
        throw std::runtime_error("No process attached.");
    }
    if (_processes.find(_pid) == _processes.end()) {
        throw std::runtime_error("Process is not being debugged.");
    }
    _processes.erase(_pid);
    _pid = 0;
};

void ILowLevelDebugger::attach(pid_t pid)
{
    if (pid <= 0) {
        throw std::invalid_argument("Invalid process ID.");
    }
    _pid = pid;
    if (_processes.find(pid) != _processes.end()) {
        throw std::runtime_error("Process is already being debugged.");
    }
    _processes[pid] = 1;
};

ILowLevelDebugger::ProcessInfo::Counter& ILowLevelDebugger::ProcessInfo::Counter::operator++()
{
    ++_value;
    return *this;
}


ILowLevelDebugger::ProcessInfo::Counter ILowLevelDebugger::ProcessInfo::Counter::operator++(int)
{
    ILowLevelDebugger::ProcessInfo::Counter temp = *this;
    ++_value;
    return temp;
}

void ILowLevelDebugger::ProcessInfo::Counter::increment()
{
    ++_value;
}

unsigned int ILowLevelDebugger::ProcessInfo::Counter::value() const
{
    return _value;
}

ILowLevelDebugger::Context ILowLevelDebugger::Context::empty()
{
    return ILowLevelDebugger::Context{};
}
