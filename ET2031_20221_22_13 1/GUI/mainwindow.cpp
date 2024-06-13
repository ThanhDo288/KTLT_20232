#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Hopdong.h"
#include <QString>
#include <QDebug>
#include <QListWidgetItem>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnFind_released()
{
    int x = 0; //dùng để kiểm tra xem liệu có tìm thấy tên hay không
    QString findcmt = ui->linecmt->text();
    QString findloaixe = ui->lineloaixe->text();
    int findngaythue = ui->linengaythue->text().toInt();
    int findthangthue = ui->linethangthue->text().toInt();
    int findnamthue = ui->linenamthue->text().toInt();
    int findngaytra = ui->linengaytra->text().toInt();
    int findthangtra = ui->linethangtra->text().toInt();
    int findnamtra = ui->linenamtra->text().toInt();
    for (int i = 0; i < m_Hopdong.size(); i++) {
        if (ui->linecmt->text() == "") {
            findcmt = m_Hopdong[i]->getcmt();
        }
        if (ui->lineloaixe->text() == "") {
            findloaixe = m_Hopdong[i]->getloaixe();
        }
        if (ui->linengaythue->text() == "") {
            findngaythue = m_Hopdong[i]->getngaythue();
        }
        if (ui->linethangthue->text() == "") {
            findthangthue = m_Hopdong[i]->getthangthue();
        }
        if (ui->linenamthue->text() == "") {
            findnamthue = m_Hopdong[i]->getnamthue();
        }
        if (ui->linengaytra->text() == "") {
            findngaytra = m_Hopdong[i]->getngaytra();
        }
        if (ui->linethangtra->text() == "") {
            findthangtra = m_Hopdong[i]->getthangtra();
        }
        if (ui->linenamtra->text() == "") {
            findnamtra = m_Hopdong[i]->getnamtra();
        }
}


void MainWindow::on_btnThemmoi_released()
{
    QString find = ui->linehoten->text();
    for (int i = 0; i < m_Hopdong.size(); i++) {
        if (m_Hopdong[i]->gethoten() == find) {
            m_Hopdong[i]->setngaythue(ui->linengaythue->text().toInt());
            m_Hopdong[i]->setthangthue(ui->linethangthue->text().toInt());
            m_Hopdong[i]->setnamthue(ui->linenamthue->text().toInt());
            m_Hopdong[i]->setngaytra(ui->linengaytra->text().toInt());
            m_Hopdong[i]->setthangtra(ui->linethangtra->text().toInt());
            m_Hopdong[i]->setnamtra(ui->linenamtra->text().toInt());

        }
    }
}


void MainWindow::on_btnCapnhat_released()
{
    QString capnhat = ui->linehoten->text();
    for (int i = 0; i < m_Hopdong.size(); i++) {
        if (m_Hopdong[i]->gethoten()== capnhat) {
            m_Hopdong.erase(m_Hopdong.begin() +i);
        }
    }
}

