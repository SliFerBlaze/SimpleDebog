#pragma once

#include "DebugModule.hh"
#include <QPushButton>

class StepModule : public DebugModule {
    Q_OBJECT

public:
    explicit StepModule(QWidget* parent = nullptr);

signals:
    void StepRequested();
    
private:
    QPushButton* stepButton;
};
