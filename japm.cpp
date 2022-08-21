#include "japm.h"
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
    readDataFromFile();
    displayData();
}

void JAPM::readDataFromFile() {
    if (!dataFile.isEmpty()) {
        std::string fileStr;
        std::ifstream f;
        f.open(dataFile.toStdString());
        std::getline(f, fileStr);
        f.close();
        std::stringstream stream(fileStr, std::ios_base::in);
        stream << std::noskipws;
        data.clear();
        data_t elem;
        while (stream >> elem) {
            data.push_back(elem);
        }
    }
}

void JAPM::on_pushButtonSaveFile_clicked()
{
    saveFile();
}

void JAPM::saveFile() {
    if (!dataFile.isEmpty()) {
        std::stringstream stream(std::ios_base::out);
        for (data_t elem : data) {
            stream << elem;
        }
        std::ofstream f;
        f.open(dataFile.toStdString(), std::ios::binary);
        f << stream.str();
        f.close();
    }
}

data_t JAPM::getData() {
    std::string name = ui->lineEditName->text().toStdString();
    std::string login = ui->lineEditLogin->text().toStdString();
    std::string password = ui->lineEditPassword->text().toStdString();
    std::string info = ui->lineEditInfo->text().toStdString();
    return data_t({}, name, login, password, info);
}

void JAPM::clearInput() {
    ui->lineEditName->clear();
    ui->lineEditLogin->clear();
    ui->lineEditPassword->clear();
    ui->lineEditInfo->clear();
}

void JAPM::on_pushButtonAddEntry_clicked()
{
    data_t newElem = getData();
    size_t id;
    bool exist = false;
    for (size_t i = 0; i < data.size(); ++i) {
        data_t elem = data[i];
        if (newElem.name == elem.name) {
            exist = true;
            id = i;
            break;
        }
    }
    if (exist) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Replace", "Entry already exists, replace?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            data[id] = newElem;
            clearInput();
        }
    } else {
        data.push_back(newElem);
        clearInput();
    }

    displayData();
}

void JAPM::setTableData(int64_t i, const data_t & elem) {
    QTableWidgetItem* itemName = new QTableWidgetItem(QString::fromStdString(elem.name));
    ui->tableWidgetData->setItem(i, 0, itemName);

    QTableWidgetItem* itemLogin = new QTableWidgetItem(QString::fromStdString(elem.login));
    ui->tableWidgetData->setItem(i, 1, itemLogin);

    QTableWidgetItem* itemPassword = new QTableWidgetItem(QString::fromStdString(elem.password));
    ui->tableWidgetData->setItem(i, 2, itemPassword);

    QTableWidgetItem* itemInfo = new QTableWidgetItem(QString::fromStdString(elem.info));
    ui->tableWidgetData->setItem(i, 3, itemInfo);
}

void JAPM::displayData() {
    int64_t n = data.size();
    ui->tableWidgetData->setRowCount(n);
    ui->tableWidgetData->setColumnCount(4);
    for (int64_t i = 0; i < n; ++i) {
        setTableData(i, data[i]);
    }
}
