# Use Qt Widgets module
QT += widgets

# C++ configuration
CONFIG += c++20 console
TEMPLATE = app
TARGET = simpledebog

# Include directories
INCLUDEPATH += \
    src \
    tests/interface \
    tests/shared \
    tests/shared/models \
    tests/backend

# Source files (.cpp)
SOURCES += \
    src/MainWindow.cpp \
    src/GuiAdapter.cpp \
    src/modules/StepModule.cpp \
    src/modules/CodeModule.cpp \
    src/modules/StackModule.cpp \
    src/modules/BreakpointsModule.cpp \
    src/main.cpp

# Header files (.hh)
HEADERS += \
    src/MainWindow.hh \
    src/GuiAdapter.hh \
    src/modules/StepModule.hh \
    src/modules/CodeModule.hh \
    src/modules/StackModule.hh \
    src/modules/DebugModule.hh \
    src/modules/BreakpointsModule.hh \
    tests/interface/IDebugger.hh \
    tests/interface/DebugEventListener.hh \
    tests/interface/ICommand.hh \
    tests/shared/models/StackFrame.hh \
    tests/backend/MockDebugger.hh
