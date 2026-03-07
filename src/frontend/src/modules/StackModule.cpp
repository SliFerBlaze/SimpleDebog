#include "StackModule.hh"
#include <QVBoxLayout>

StackModule::StackModule(QWidget* parent)
    : DebugModule("stack", "Stack Module", parent)
{
    QWidget* content = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(content);

    stackButton = new QPushButton("Stack", content);
    layout->addWidget(stackButton);

    setWidget(content);

    connect(stackButton, &QPushButton::clicked,
            this, &StackModule::StackRequested);
}
