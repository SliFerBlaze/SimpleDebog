#include "StepModule.hh"
#include <QVBoxLayout>

StepModule::StepModule(QWidget* parent)
    : DebugModule("step", "Step Module", parent)
{
    QWidget* content = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(content);

    stepButton = new QPushButton("Step", content);
    layout->addWidget(stepButton);

    setWidget(content);

    connect(stepButton, &QPushButton::clicked,
            this, &StepModule::StepRequested);
}
