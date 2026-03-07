#pragma once

#include <QMainWindow>
#include <QMap>
#include <QString>
#include <QMenu>

#include "modules/DebugModule.hh"
#include "modules/StepModule.hh"
#include "modules/CodeModule.hh"
#include "modules/StackModule.hh"
#include "modules/BreakpointsModule.hh"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

    void registerModule(DebugModule* module,
                        Qt::DockWidgetArea area = Qt::LeftDockWidgetArea);
    void finalizeTabOrder();

    void showModule(const QString& id);
    void hideModule(const QString& id);

    bool hasModule(const QString& id) const;
    DebugModule* getModule(const QString& id);

private:
    QMenu* viewMenu;

    QMap<QString, DebugModule*> modules;
    QMap<QString, QAction*> moduleActions;
};
