#include "BreakpointsModule.hh"

BreakpointsModule::BreakpointsModule(QWidget* parent)
    : DebugModule("breakpoints", "Breakpoints", parent)
{
    list = new QListWidget(this);
    list->setMouseTracking(true);
    setWidget(list);

    connect(list, &QListWidget::itemEntered,
            this, [this](QListWidgetItem* item) {
                emit breakpointHovered(item->data(Qt::UserRole).toString());
            });
}

void BreakpointsModule::addBreakpoint(const QString& id,
                                      const QString& displayText)
{
    auto* item = new QListWidgetItem(displayText);
    item->setData(Qt::UserRole, id);
    list->addItem(item);
}
