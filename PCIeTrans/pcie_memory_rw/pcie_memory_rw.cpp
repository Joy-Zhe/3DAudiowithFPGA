#include "pcie_memory_rw.h"
#include "qdir.h"
#include "ui_pcie_memory_rw.h"
#include <QDebug>
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QTextBrowser>
#include <QFile>
#include <QMimeData>
#include <iostream>
#include <QThread>
#include "AudioFile.h"
#include <QtConcurrent/QtConcurrent>

pcie_memory_rw::pcie_memory_rw(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::pcie_memory_rw)
{
    ui->setupUi(this);
    //初始化PCIe XDMA设备
    if(pcie_init()<0){
        QMessageBox::information(this,"ERROR","PCIe init error");
        exit(-1);
    }

    //打开PCIe XDMA设备
    if(pcie_open()<0){
        QMessageBox::information(this,"ERROR","PCIe open error");
        exit(-1);
    }
}

pcie_memory_rw::~pcie_memory_rw()
{
    pcie_close();
    delete ui;
}

//点击“发送数据”按钮后，执行写数据到FPGA侧Memory并读回
void pcie_memory_rw::on_btnSnd_clicked()
{
//    if(write_fpga_mem())
//        read_fpga_mem();
    delay_fpga_write();
}

//void pcie_memory_rw::on_wavProcessButton_clicked() {
//    QString snd_text = ui->txtEdit->toPlainText();
//    if (snd_text.startsWith("file:///")) {
//        // Remove the "file:///" prefix
//        snd_text.remove(0, 8); // 8 is the length of "file:///"
//    }

//    std::string wavPath = snd_text.toStdString();
//    //Process wave data
//    processWavData(wavPath);
//    //-------------------------------------------
//}

void pcie_memory_rw::on_wavProcessButton_clicked() {
    QString snd_text = ui->txtEdit->toPlainText();
    if (snd_text.startsWith("file:///")) {
        // Remove the "file:///" prefix
        snd_text.remove(0, 8); // 8 is the length of "file:///"
    }

    std::string wavPath = snd_text.toStdString();

    QtConcurrent::run([this, wavPath]() {
        processWavData(wavPath);
    });
}

void pcie_memory_rw::erase_fpga_mem() {
    int size = 1024 * 16;
    uint16_t* dataArray = (uint16_t *)malloc(sizeof(uint16_t) * size);
    for(int i = 0; i < size; i++) {
        dataArray[i] = 0;
    }
    h2c_transfer(0, size, dataArray);
    delete[] dataArray;
}

// write for debug
int pcie_memory_rw::write_fpga_mem()
{
//    erase_fpga_mem();
    QString snd_text = ui->txtEdit->toPlainText();
    if (snd_text.startsWith("file:///")) {
        // Remove the "file:///" prefix
        snd_text.remove(0, 8); // 8 is the length of "file:///"
    }

    std::string wavPath = snd_text.toStdString();
    //Process wave data
    processWavData(wavPath);
    //-------------------------------------------


//    QByteArray snd_byteArray = snd_text.toUtf8();
//    if(*snd_byteArray.data())
//        data_size = h2c_transfer(0, snd_byteArray.size(),snd_byteArray.data());
//    else
//        return 0;
    int size = pcie_write_data.size();
    uint16_t* dataArray = (uint16_t *)malloc(sizeof(uint16_t) * size);
    for(int i = 0; i < size; i++) {
        dataArray[i] = pcie_write_data[i];
//        qDebug() << "write:" << dataArray[i];
    }

    if(!pcie_write_data.empty()){
        data_size = h2c_transfer(0, size, dataArray);
        pcie_write_data.clear();
        free(dataArray);
    }
    else
        return 0;
    return 1;
}

// read for debug
void pcie_memory_rw::read_fpga_mem()
{
////    QByteArray rcv_byteArray;
////    rcv_byteArray.resize(data_size);
////    QThread::msleep(1000);
//    QByteArray rcv_byteArray;
//    rcv_byteArray.resize(data_size);

//    uint16_t* rcvArray = (uint16_t*)malloc(sizeof(uint16_t) * data_size);

////    c2h_transfer(0, data_size, rcv_byteArray.data());
//    c2h_transfer(0, data_size, rcvArray);
//    qDebug() << "Data size:" << data_size;
//    for (int i = 0; i < 5; i++) {
//        uint16_t tmp = rcvArray[i];
//        qDebug() << tmp;
//    }
//    QString rcv_text;
//    for (int i = 0; i < data_size; i++) {
//        rcv_text += QString("%1 ").arg(rcvArray[i], 4, 16, QLatin1Char('0'));
//        if(i < 5)
//            qDebug() << rcv_text;
//    }
//    ui->txtBro->append(rcv_text);
}

void pcie_memory_rw::processWavData(const std::string &filePath) {
// old one
    ui->proBox->setChecked(false);
    QString currentDir = QCoreApplication::applicationDirPath();
    std::string curDir = currentDir.toStdString();
    AudioFile<uint16_t> waveFile;
    waveFile.load(filePath);

    uint16_t x;
    uint16_t y;
    uint16_t z;
    uint16_t st1 = 0x0;
    uint16_t st2 = 0xffff;

    int cnt = 0;

//    bool breaktest = false;
    // 处理数据，设想是和xyz多线程，用个delay可能比较方便，使整首wav的读取在30s级别比较合适。
    auto samples = waveFile.samples;
    for (int i = 0; i < waveFile.getNumSamplesPerChannel(); i++) {
        if (cnt % (511 * 2) == 0) {
            x = ui->xSlider->value();
            y = ui->ySlider->value();
            z = ui->zSlider->value();
            pcie_write_data.push_back(st1);
            pcie_write_data.push_back(st2);
            pcie_write_data.push_back(x);
            pcie_write_data.push_back(y);
            pcie_write_data.push_back(z);
//            qDebug() << x << " " << y << " " << z;
            QThread::msleep(1);
        }
        for (int j = 0; j < waveFile.getNumChannels(); j++) {
            pcie_write_data.push_back(samples[j][i]);
            cnt++;
            // for debug
            if(cnt % (511 * 2) == 0) {
                tiledWavData.push_back(pcie_write_data);
                pcie_write_data.clear();
//                breaktest = true;
//                break;
            }
        }
//        if (breaktest == true)
//            break;
    }

    if(cnt % (511 * 2) != 0){
        tiledWavData.push_back(pcie_write_data);
        pcie_write_data.clear();
    }
    ui->proBox->setChecked(true);
    // ----------------------------

//    watcher.setFuture(QtConcurrent::run([this, filePath]() {
//                          ui->proBox->setChecked(false);

//                          QString currentDir = QCoreApplication::applicationDirPath();
//                          std::string curDir = currentDir.toStdString();

//                          AudioFile<uint16_t> waveFile;
//                          waveFile.load(filePath);

//                          uint16_t x, y, z;
//                          int cnt = 0;
////                          bool breaktest = false;
//                          uint16_t st1 = 0x0;
//                          uint16_t st2 = 0xffff;

//                          // 开始并发执行
//                          QFuture<void> future = QtConcurrent::run([&]() {
//                              x = ui->xSlider->value();
//                              y = ui->ySlider->value();
//                              z = ui->zSlider->value();
//                          });

//                          // 处理数据，与滑块值监视并发执行
//                          auto samples = waveFile.samples;
//                          for (int i = 0; i < waveFile.getNumSamplesPerChannel(); i++) {
//                              if (cnt % (511 * 2) == 0) {
//                                  pcie_write_data.push_back(st1);
//                                  pcie_write_data.push_back(st2);
//                                  pcie_write_data.push_back(x);
//                                  pcie_write_data.push_back(y);
//                                  pcie_write_data.push_back(z);
//                                  QThread::msleep(1);
//                              }

//                              for (int j = 0; j < waveFile.getNumChannels(); j++) {
//                                  pcie_write_data.push_back(samples[j][i]);
//                                  cnt++;

//                                  if (cnt % (511 * 2) == 0) {
//                                      tiledWavData.push_back(pcie_write_data);
//                                      pcie_write_data.clear();
//                                  }
//                              }
//                          }

//                          if (cnt % (511 * 2) != 0) {
//                              tiledWavData.push_back(pcie_write_data);
//                              pcie_write_data.clear();
//                          }

//                          // 发射信号以标记处理完成
//                          ui->proBox->setChecked(true);
//    }));
}

void pcie_memory_rw::delay_fpga_write() {
    int blockNum = tiledWavData.size();
    for(int k = 0; k < blockNum; k++){
        int size = tiledWavData[k].size();
        uint16_t* dataArray = (uint16_t *)malloc(sizeof(uint16_t) * size);
        for(int i = 0; i < size; i++) {
            dataArray[i] = tiledWavData[k][i];
            //        qDebug() << "write:" << dataArray[i];
        }

        if(!tiledWavData[k].empty()){
            data_size = h2c_transfer(0, size, dataArray);
        }
        free(dataArray);
//        QThread::usleep(static_cast<useconds_t>(1000000.0 / (44100.0 * 511.0)));  // Delay for 1/44100*511 seconds
        Sleep(static_cast<DWORD>(1000.0 / (44100.0 * 511.0)));
        // for debug
//        read_fpga_mem();
    }
    tiledWavData.clear();
    read_fpga_mem();
//    else
//        return;
    return;
}
