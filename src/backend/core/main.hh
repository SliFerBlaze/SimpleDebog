#include "DebuggerEngine.hh"
#include "backend/platform/ILowLevelDebugger.hh"
#include <thread>

void main_backend_core(DebuggerEngine &engine, ILowLevelDebugger &debugger, bool &running);
