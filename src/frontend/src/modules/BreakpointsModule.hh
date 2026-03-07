#pragma once

#include "DebugModule.hh"
#include <QListWidget>
#include <QDebug>

class BreakpointsModule : public DebugModule {
    Q_OBJECT

public:
    explicit BreakpointsModule(QWidget* parent = nullptr);

    void addBreakpoint(const QString& id,
                       const QString& displayText);
    
    void handleHovered(QListWidgetItem* item);

signals:
    void breakpointHovered(const QString& id);

private:
    QListWidget* list;
};
