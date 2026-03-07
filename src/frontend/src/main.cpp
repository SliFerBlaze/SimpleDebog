#include <QApplication>
#include "MainWindow.hh"
#include "GuiAdapter.hh"
#include "../tests/backend/MockDebugger.hh"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    MockDebugger debugger;
    GuiAdapter adapter(&debugger, &window);

    window.show();
    return app.exec();
}
