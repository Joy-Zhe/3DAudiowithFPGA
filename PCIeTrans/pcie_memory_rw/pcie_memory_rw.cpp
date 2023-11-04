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

void pcie_memory_rw::erase_fpga_mem() {
    int size = 1024 * 16;
    uint16_t* dataArray = (uint16_t *)malloc(sizeof(uint16_t) * size);
    for(int i = 0; i < size; i++) {
        dataArray[i] = 0;
    }
    h2c_transfer(0, size, dataArray);
    delete[] dataArray;
}

//写FPGA侧Memory,返回0表示无数据需要写入，返回1表示写入数据完成
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
        delete [] dataArray;
    }
    else
        return 0;
    return 1;
}

//读FPGA侧Memory并显示在接收窗口中
void pcie_memory_rw::read_fpga_mem()
{
//    QByteArray rcv_byteArray;
//    rcv_byteArray.resize(data_size);
//    QThread::msleep(1000);
    QByteArray rcv_byteArray;
    rcv_byteArray.resize(data_size);

    uint16_t* rcvArray = (uint16_t*)malloc(sizeof(uint16_t) * data_size);

//    c2h_transfer(0, data_size, rcv_byteArray.data());
    c2h_transfer(0, data_size, rcvArray);
    qDebug() << "Data size:" << data_size;
//    QString rcv_text = rcv_byteArray.data();
//    for (int i = 0; i < data_size; i++) {
//        uint16_t tmp = rcvArray[i];
//        qDebug() << tmp;
//    }
    QString rcv_text;
    for (int i = 0; i < data_size; i++) {
        rcv_text += QString("%1 ").arg(rcvArray[i], 4, 16, QLatin1Char('0'));
    }
    ui->txtBro->append(rcv_text);
}

void pcie_memory_rw::processWavData(const std::string &filePath) {
    QString currentDir = QCoreApplication::applicationDirPath();
    std::string curDir = currentDir.toStdString();

    std::ofstream outputFile("D:/code/3DAudioWithFPGA/PCIeTrans/build-pcie_memory_rw-Desktop_Qt_6_6_0_MSVC2019_64bit-Release/pcie_write.txt");
    AudioFile<uint16_t> waveFile;
    waveFile.load(filePath);
    int numSamples = waveFile.getNumSamplesPerChannel();
    int numChannels = waveFile.getNumChannels();
    auto sampleRate = waveFile.getSampleRate();
    auto bitDepth = waveFile.getBitDepth();

    // Write to the file
//    outputFile << "numSamples: " << numSamples << std::endl;
//    outputFile << "numChannels: " << numChannels << std::endl;
//    outputFile << "sampleRate: " << sampleRate << std::endl;
//    outputFile << "bitDepth: " << bitDepth << std::endl;

    uint16_t x = ui->xSlider->value();
    uint16_t y = ui->ySlider->value();
    uint16_t z = ui->zSlider->value();

    outputFile << x << y << z << std::endl;
    outputFile << curDir << std::endl;
//    pcie_write_data[0] = x;
//    pcie_write_data[1] = y;
//    pcie_write_data[2] = z;
    uint16_t st1 = 0x0;
    uint16_t st2 = 0xffff;

    int cnt = 0;
//    qDebug() << "当前运行位置的目录：" << currentDir;

    bool breaktest = false;
    // 处理数据，设想是和xyz多线程，用个delay可能比较方便，使整首wav的读取在30s级别比较合适。
    auto samples = waveFile.samples;
    for (int i = 0; i < waveFile.getNumSamplesPerChannel(); i++) {
        if (cnt % (512 * 2) == 0) {
            pcie_write_data.push_back(st1);
            pcie_write_data.push_back(st2);
            pcie_write_data.push_back(x);
            pcie_write_data.push_back(y);
            pcie_write_data.push_back(z);
        }
        for (int j = 0; j < waveFile.getNumChannels(); j++) {
            // Write each sample to the file
            outputFile << samples[j][i] << std::endl;
            pcie_write_data.push_back(samples[j][i]);
            cnt++;
            // for debug
//            if(cnt == 10) {
//                breaktest = true;
//                break;
//            }
            if(cnt % (512 * 2) == 0) {
                tiledWavData.push_back(pcie_write_data);
                pcie_write_data.clear();
//                breaktest = true;
//                break;
            }
        }
//        if (breaktest == true)
//            break;
    }

//    for (auto it : pcie_write_data) {
//        qDebug() << "write:" << it;
//    }
    if(cnt % (512 * 2) != 0){
        tiledWavData.push_back(pcie_write_data);
        pcie_write_data.clear();
    }
    outputFile.close();
//    waveFile.save(curDir + "/newWave.wav");
    waveFile.save("D:/code/3DAudioWithFPGA/PCIeTrans/build-pcie_memory_rw-Desktop_Qt_6_6_0_MSVC2019_64bit-Release/newWaveTest.wav");
}

void pcie_memory_rw::delay_fpga_write() {
    QString snd_text = ui->txtEdit->toPlainText();
    if (snd_text.startsWith("file:///")) {
        // Remove the "file:///" prefix
        snd_text.remove(0, 8); // 8 is the length of "file:///"
    }

    std::string wavPath = snd_text.toStdString();
    //Process wave data
    processWavData(wavPath);
    //-------------------------------------------

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
            free(dataArray);
        }
        QThread::msleep(11);
        // for debug
        read_fpga_mem();
    }
    tiledWavData.clear();
//    else
//        return;
    return;
}
