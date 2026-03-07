#include "CodeModule.hh"

CodeModule::CodeModule(QWidget* parent)
    : DebugModule("code", "Code Module", parent)
{
    tabs = new QTabWidget(this);
    tabs->setTabsClosable(true);
    tabs->setMovable(true);

    setWidget(tabs);
}

QPlainTextEdit* CodeModule::createEditor()
{
    auto* editor = new QPlainTextEdit;
    editor->setReadOnly(true);

    QFont font("Monospace");
    font.setStyleHint(QFont::TypeWriter);
    editor->setFont(font);

    editor->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(editor, &QPlainTextEdit::customContextMenuRequested,
            this, [this, editor](const QPoint& pos) {
                handleContextMenu(editor, pos);
            });

    return editor;
}

void CodeModule::openSource(const QString& fileId,
                            const QString& displayName,
                            const QString& text)
{
    if (editors.contains(fileId)) {
        tabs->setCurrentWidget(editors[fileId]);
        return;
    }

    auto* editor = createEditor();
    editor->setPlainText(text);

    tabs->addTab(editor, displayName);
    editors[fileId] = editor;
}

QString CodeModule::currentFileId() const
{
    QWidget* current = tabs->currentWidget();
    if (!current)
        return {};

    for (auto it = editors.begin(); it != editors.end(); ++it) {
        if (it.value() == current)
            return it.key();
    }

    return {};
}

void CodeModule::handleContextMenu(QPlainTextEdit* editor,
                                   const QPoint& pos)
{
    QTextCursor cursor = editor->cursorForPosition(pos);
    cursor.select(QTextCursor::WordUnderCursor);
    QString word = cursor.selectedText();

    if (word.trimmed().isEmpty())
        return;

    highlightWord(editor, cursor);

    int line = cursor.blockNumber() + 1;

    QMenu menu;
    QAction* lineBp = menu.addAction("Add breakpoint at line");
    QAction* functionBp = menu.addAction("Add breakpoint on function call");
    QAction* variableBp = menu.addAction("Add watchpoint on variable");

    QAction* selected = menu.exec(editor->mapToGlobal(pos));
    if (!selected) {
        clearTemporaryHighlight();
        return;
    }

    QString fileId = currentFileId();
    if (fileId.isEmpty()) {
        clearTemporaryHighlight();
        return;
    }

    QString bpId = fileId + ":" + QString::number(line) + ":" + word;

    Breakpoint bp{fileId, line, word, ""};
    breakpoints[bpId] = bp;

    QString label = fileId + ":" + QString::number(line);

    emit breakpointRequested(bpId, label);
    clearTemporaryHighlight();
}

void CodeModule::highlightWord(QPlainTextEdit* editor,
                               const QTextCursor& cursor)
{
    QTextEdit::ExtraSelection selection;
    selection.cursor = cursor;
    selection.format.setBackground(QColor(255, 255, 0, 120));

    QList<QTextEdit::ExtraSelection> extras;
    extras.append(selection);

    editor->setExtraSelections(extras);
}

void CodeModule::highlightBreakpoint(const QString& breakpointId)
{
    if (!breakpoints.contains(breakpointId))
        return;

    const Breakpoint& bp = breakpoints[breakpointId];
    if (!editors.contains(bp.fileId))
        return;

    QPlainTextEdit* editor = editors[bp.fileId];
    tabs->setCurrentWidget(editor);

    QTextCursor cursor(editor->document()->findBlockByLineNumber(bp.line - 1));
    cursor.select(QTextCursor::LineUnderCursor);

    QTextEdit::ExtraSelection selection;
    selection.cursor = cursor;
    selection.format.setBackground(QColor(255, 0, 0, 80));

    QList<QTextEdit::ExtraSelection> extras;
    extras.append(selection);

    editor->setExtraSelections(extras);
}

void CodeModule::clearTemporaryHighlight()
{
    currentSelections.clear();

    if (auto editor = currentEditor())
        editor->setExtraSelections(currentSelections);
}

QPlainTextEdit* CodeModule::currentEditor() const
{
    if (!tabs)
        return nullptr;

    return qobject_cast<QPlainTextEdit*>(tabs->currentWidget());
}
