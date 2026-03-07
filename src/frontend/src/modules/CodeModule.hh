#pragma once

#include "DebugModule.hh"
#include <QTabWidget>
#include <QPlainTextEdit>
#include <QMap>
#include <QTextBlock>
#include <QFont>
#include <QMenu>

class CodeModule : public DebugModule {
    Q_OBJECT

public:
    explicit CodeModule(QWidget* parent = nullptr);

    void openSource(const QString& fileId,
                    const QString& displayName,
                    const QString& text);

    QString currentFileId() const;

    void highlightBreakpoint(const QString& breakpointId);

signals:
    void breakpointRequested(const QString& breakpointId,
                             const QString& displayLabel);

private:
    struct Breakpoint {
        QString fileId;
        int line;
        QString symbol;
        QString type;
    };

    QTabWidget* tabs;
    QMap<QString, QPlainTextEdit*> editors;
    QMap<QString, Breakpoint> breakpoints;
    QList<QTextEdit::ExtraSelection> currentSelections;

    QPlainTextEdit* createEditor();
    void handleContextMenu(QPlainTextEdit* editor,
                           const QPoint& pos);
    void highlightWord(QPlainTextEdit* editor,
                       const QTextCursor& cursor);
    void clearTemporaryHighlight();

    QPlainTextEdit* currentEditor() const;
};


