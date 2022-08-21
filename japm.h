#ifndef JAPM_H
#define JAPM_H

#include "data.h"
#include <fstream>
#include <vector>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class JAPM; }
QT_END_NAMESPACE

class JAPM : public QMainWindow
{
    Q_OBJECT

public:
    JAPM(QWidget *parent = nullptr);
    ~JAPM();

private slots:
    void on_pushButtonSaveAs_clicked();

    void on_pushButtonOpenFile_clicked();

    void on_pushButtonSaveFile_clicked();

    void on_pushButtonAddEntry_clicked();

private:
    Ui::JAPM *ui;
    QString dataFile;
    std::vector<data_t> data;

    void saveFile();
    void readDataFromFile();
    void displayData();
    data_t getData();
    void clearInput();
    void setTableData(int64_t, const data_t &);
};
#endif // JAPM_H
