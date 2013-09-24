#include <QtWidgets/QApplication>
#include "rocatool.h"
#include "Interface.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    RocaTool rt;
    rt.show();

    return app.exec();
}

