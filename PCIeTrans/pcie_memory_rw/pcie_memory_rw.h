#ifndef PCIE_MEMORY_RW_H
#define PCIE_MEMORY_RW_H

#include <QMainWindow>
#include <QByteArray>
#include <vector>
#include "pcie_dev.h"
#include <QFutureWatcher>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class pcie_memory_rw; }
QT_END_NAMESPACE


class pcie_memory_rw : public QMainWindow
{
    Q_OBJECT
signals:
    void wavFileDropped(const QString &filePath);
    void startProcessing();
public:
    long data_size;
    pcie_memory_rw(QWidget *parent = nullptr);
    ~pcie_memory_rw();

private slots:
    void on_btnSnd_clicked();
    void on_wavProcessButton_clicked();

private:
//    void dragEnterEvent(QDragEnterEvent *event);
//    void dropEvent(QDropEvent *event);
    Ui::pcie_memory_rw *ui;
    int write_fpga_mem();
    void read_fpga_mem();
    void erase_fpga_mem();
    void delay_fpga_write(); // write every 512 * 2 samples, delay for 11.6ms
    void processWavData(const std::string &filePath); // process wav file data
    std::vector<uint16_t> pcie_write_data; // x, y, z, wave data(L R L R ... each 32bits)
    std::vector<std::vector<uint16_t>> tiledWavData;
//    QByteArray wavData; // save wav data
};
#endif // PCIE_MEMORY_RW_H
