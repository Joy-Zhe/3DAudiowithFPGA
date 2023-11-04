#include "pcie_memory_rw.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    pcie_memory_rw w;
    w.setWindowTitle("早知道，还是FPGA/(ㄒoㄒ)/~~");
    w.show();
    return a.exec();
}
