#pragma once

#include "DebugModule.hh"
#include <QPushButton>

class StackModule : public DebugModule {
    Q_OBJECT

public:
    explicit StackModule(QWidget* parent = nullptr);

signals:
    void StackRequested();
    
private:
    QPushButton* stackButton;
};
