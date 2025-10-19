#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Widget window;
    window.setWindowTitle("Трекер задач");
    window.resize(800,500);

    window.show();
    return app.exec();
}
