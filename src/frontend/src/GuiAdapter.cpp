#include "GuiAdapter.hh"

GuiAdapter::GuiAdapter(IDebugger* debugger, MainWindow* ui)
    : debugger(debugger), ui(ui)
{
    debugger->addListener(this);

    if (auto* step = dynamic_cast<StepModule*>(ui->getModule("step"))) {
        connect(step, &StepModule::StepRequested,
                this, &GuiAdapter::handleStepRequest);
    }

    auto* code = dynamic_cast<CodeModule*>(ui->getModule("code"));
    breakpointsModule = dynamic_cast<BreakpointsModule*>(ui->getModule("breakpoints"));

    if (code && breakpointsModule) {
        connect(code, &CodeModule::breakpointRequested,
                this, &GuiAdapter::handleBreakpointRequest);

        connect(breakpointsModule,
                &BreakpointsModule::breakpointHovered,
                code,
                &CodeModule::highlightBreakpoint);
    }

}

void GuiAdapter::handleBreakpointRequest(const QString& id,
                                         const QString& label)
{
    if (!breakpointsModule)
        return;

    breakpointsModule->addBreakpoint(id, label);
}

void GuiAdapter::handleStepRequest()
{
    debugger->executeCommand(std::make_unique<StepCommand>());
}

void GuiAdapter::onEvent(const DebugEvent& event)
{
    // // Broadcast to all modules
    // for (const auto& module : ui->findChildren<DebugModule*>()) {
    //     switch (event.type) {
    //         case DebugEventType::BreakpointHit:
    //             module->onBreakpointHit(event.address);
    //             break;
    //         case DebugEventType::StackUpdated:
    //             module->onStackUpdated(event.stackFrames);
    //             break;
    //         default:
    //             break;
    //     }
    // }
}
