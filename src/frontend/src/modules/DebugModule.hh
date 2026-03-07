#pragma once

#include <QDockWidget>
#include <QString>

class DebugModule : public QDockWidget
{
    Q_OBJECT

public:
    explicit DebugModule(const QString& id,
                         const QString& title,
                         QWidget* parent = nullptr)
        : QDockWidget(title, parent)
        , m_id(id)
        , m_title(title)
    {
        setFocusPolicy(Qt::StrongFocus);
    }

    virtual ~DebugModule() = default;

    QString id() const { return m_id; }
    QString title() const { return m_title; }

private:
    QString m_id;
    QString m_title;
};
