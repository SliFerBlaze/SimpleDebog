#include "MainWindow.hh"

#include <QMenuBar>
#include <QAction>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    resize(1920, 1080);
    viewMenu = menuBar()->addMenu("View");
    menuBar()->setFocusPolicy(Qt::NoFocus);

    StepModule* stepModule = new StepModule(this);
    CodeModule *codeModule = new CodeModule(this);
    StackModule *stackModule = new StackModule(this);
    BreakpointsModule* breakpointsModule = new BreakpointsModule(this);

    registerModule(stepModule);
    registerModule(codeModule);
    registerModule(stackModule);
    registerModule(breakpointsModule, Qt::RightDockWidgetArea);

    finalizeTabOrder();

    codeModule->openSource(
        "main.cpp",
        "main.cpp",
        R"(#include <iostream>

int main() {
    int x;
    if (x > 0)
        std::cout << x << std::endl;
}
)");

    codeModule->openSource(
        "utils.cpp",
        "utils.cpp",
        "void helper() {}\n"
    );

    setStyleSheet(R"(
    QDockWidget {
        background-color: #bbbbbb;
    }

    QDockWidget::title {
        background-color: #bbbbbb;
        color: white;
        padding-left: 6px;
        text-align: left;
        font-weight: bold;
    }
)");

    showModule("code");
    showModule("breakpoints");
}

void MainWindow::registerModule(DebugModule* module,
                                Qt::DockWidgetArea area)
{
    const QString id = module->id();

    if (modules.contains(id))
        return;

    modules[id] = module;

    addDockWidget(area, module);
    module->hide();

    QAction* action = new QAction(module->title(), this);
    action->setCheckable(true);

    connect(action, &QAction::triggered, this,
            [this, id](bool checked) {
                if (checked)
                    showModule(id);
                else
                    hideModule(id);
            });

    connect(module, &QDockWidget::visibilityChanged,
            action, &QAction::setChecked);

    viewMenu->addAction(action);
    moduleActions[id] = action;
}

void MainWindow::finalizeTabOrder()
{
    DebugModule* prev = nullptr;

    for (auto* module : modules) {
        if (prev)
            setTabOrder(prev, module);
        prev = module;
    }
}

void MainWindow::showModule(const QString& id)
{
    if (!modules.contains(id))
        return;

    modules[id]->show();
    moduleActions[id]->setChecked(true);
}

void MainWindow::hideModule(const QString& id)
{
    if (!modules.contains(id))
        return;

    modules[id]->hide();
    moduleActions[id]->setChecked(false);
}

bool MainWindow::hasModule(const QString& id) const
{
    return modules.contains(id);
}

DebugModule* MainWindow::getModule(const QString& id)
{
    return modules.value(id, nullptr);
}
