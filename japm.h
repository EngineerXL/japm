#ifndef JAPM_H
#define JAPM_H

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <fstream>
#include <vector>

#include "./data/data.h"
#include "./encrypter/encrypter_aes256.h"
#include "./substr/pattern_text_search.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class JAPM;
}
QT_END_NAMESPACE

class JAPM : public QMainWindow {
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

    void on_checkBoxTags_stateChanged(int);

    void on_pushButtonSort_clicked();

    void on_lineEditSearch_textEdited(const QString &);

    void on_radioButtonName_clicked();

    void on_radioButtonTags_clicked();

    void on_checkBoxCaseSensitive_stateChanged(int);

   private:
    Ui::JAPM *ui;

    uint64_t savesCnt = 0;

    QString dataFile;
    std::vector<data_t> data;
    std::vector<size_t> visible;
    std::string key;
    encrypter_t encr;

    const char DATA_DELIMITER = ';';
    const char DATA_END = '$';

    void saveFile();
    void readDataFromFile();
    void infoBadFileOrKey();
    void displayData();
    std::vector<std::string> getTags();
    data_t getData();
    void clearInput();
    void filterData();
    void setTableData(size_t, const data_t &, bool);
    bool findByName(const std::string &, size_t &);
    bool getKey();
};
#endif  // JAPM_H
