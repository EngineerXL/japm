#ifndef JAPM_H
#define JAPM_H

#include "data.h"
#include "pattern_text_search.h"
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

    void on_pushButtonRemove_clicked();

    void on_checkBoxTags_stateChanged(int arg1);

    void on_pushButtonSort_clicked();

    void on_lineEditSearch_textEdited(const QString &arg1);

    void on_radioButtonName_clicked();

    void on_radioButtonTags_clicked();

    void on_checkBoxCaseSensitive_stateChanged(int arg1);

private:
    Ui::JAPM *ui;
    QString dataFile;
    std::vector<data_t> data;
    std::vector<size_t> visible;

    void saveFile();
    void readDataFromFile();
    void displayData();
    std::vector<std::string> getTags();
    data_t getData();
    void clearInput();
    void filterData();
    void setTableData(size_t, const data_t &, bool);
    bool findByName(const std::string &, size_t &);
};
#endif // JAPM_H
