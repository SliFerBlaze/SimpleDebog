#pragma once
#include <QObject>
#include "../tests/interface/IDebugger.hh"
#include "../tests/interface/DebugEventListener.hh"
#include "../tests/interface/ICommand.hh"

#include "modules/StepModule.hh"
#include "modules/CodeModule.hh"
#include "modules/BreakpointsModule.hh"

#include "MainWindow.hh"

class GuiAdapter : public QObject, public DebugEventListener {
    Q_OBJECT
public:
    GuiAdapter(IDebugger* debugger, MainWindow* ui);

    void onEvent(const DebugEvent& event) override;

private slots:
    void handleStepRequest();
    void handleBreakpointRequest(const QString& id,
                                 const QString& label);
private:
    BreakpointsModule* breakpointsModule = nullptr;
    IDebugger* debugger;
    MainWindow* ui;

};
