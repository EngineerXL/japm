#include "japm.h"
#include "QFileDialog"
#include "ui_japm.h"

JAPM::JAPM(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::JAPM)
{
    ui->setupUi(this);
}

JAPM::~JAPM()
{
    delete ui;
}

void JAPM::on_pushButtonSaveAs_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as", ".");
    ui->lineEditFileName->setText(fileName);
    dataFile = fileName;
    saveFile();
}

void JAPM::on_pushButtonOpenFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open file", ".");
    ui->lineEditFileName->setText(fileName);
    dataFile = fileName;
}

void JAPM::on_pushButtonSaveFile_clicked()
{
    saveFile();
}

void JAPM::saveFile() {
    if (!dataFile.isEmpty()) {
        std::ofstream f;
        f.open(dataFile.toStdString(), std::ios::binary);
        for (data_t elem : data) {
            f << elem;
        }
        f.close();
    }
}

void JAPM::on_pushButtonAddEntry_clicked()
{
    std::string name = ui->lineEditName->text().toStdString();
    std::string login = ui->lineEditLogin->text().toStdString();
    std::string password = ui->lineEditPassword->text().toStdString();
    data.push_back(data_t(name, login, password));
}
