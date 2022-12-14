#include "japm.h"
#include "ui_japm.h"

JAPM::JAPM(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::JAPM)
{
    ui->setupUi(this);
    ui->checkBoxTags->setChecked(true);
    ui->tableWidgetData->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
    filterData();
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

std::vector<std::string> JAPM::getTags() {
    std::stringstream stream(ui->lineEditTags->text().toStdString(), std::ios_base::in);
    std::vector<std::string> res;
    std::string s;
    while (stream >> s) {
        res.push_back(s);
    }
    return res;
}

data_t JAPM::getData() {
    std::vector<std::string> tags = getTags();
    std::string name = ui->lineEditName->text().toStdString();
    std::string login = ui->lineEditLogin->text().toStdString();
    std::string password = ui->lineEditPassword->text().toStdString();
    std::string info = ui->lineEditInfo->text().toStdString();
    return data_t(tags, name, login, password, info);
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
    bool exist = findByName(newElem.name, id);
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
    filterData();
}

void JAPM::setTableData(size_t i, const data_t & elem, bool showTags) {

    if (showTags) {
        QTableWidgetItem* itemName = new QTableWidgetItem(QString::fromStdString(elem.tagsToString()));
        ui->tableWidgetData->setItem(i, 0, itemName);
    }

    QTableWidgetItem* itemName = new QTableWidgetItem(QString::fromStdString(elem.name));
    ui->tableWidgetData->setItem(i, 0 + showTags, itemName);

    QTableWidgetItem* itemLogin = new QTableWidgetItem(QString::fromStdString(elem.login));
    ui->tableWidgetData->setItem(i, 1 + showTags, itemLogin);

    QTableWidgetItem* itemPassword = new QTableWidgetItem(QString::fromStdString(elem.password));
    ui->tableWidgetData->setItem(i, 2 + showTags, itemPassword);

    QTableWidgetItem* itemInfo = new QTableWidgetItem(QString::fromStdString(elem.info));
    ui->tableWidgetData->setItem(i, 3 + showTags, itemInfo);
}

void JAPM::displayData() {
    ui->tableWidgetData->clear();
    size_t n = data.size();
    bool emptySearch = ui->lineEditSearch->text().isEmpty();
    if (!emptySearch) {
        n = visible.size();
    }
    ui->tableWidgetData->setRowCount(n);
    bool showTags = ui->checkBoxTags->isChecked();
    ui->tableWidgetData->setColumnCount(showTags ? 5 : 4);
    QStringList labels;
    if (showTags) {
        labels << "Tags";
    }
    labels << "Name" << "Login" << "Password" << "Info";
    ui->tableWidgetData->setHorizontalHeaderLabels(labels);
    if (emptySearch) {
        for (size_t i = 0; i < n; ++i) {
            setTableData(i, data[i], showTags);
        }
    } else {
        for (size_t i = 0; i < n; ++i) {
            setTableData(i, data[visible[i]], showTags);
        }
    }

}

bool JAPM::findByName(const std::string & s, size_t & id) {
    bool ans = false;
    for (size_t i = 0; i < data.size(); ++i) {
        if (s == data[i].name) {
            ans = true;
            id = i;
            break;
        }
    }
    return ans;
}

void JAPM::on_pushButtonRemove_clicked()
{

    std::string name = ui->lineEditRemoveName->text().toStdString();
    if (name.empty()) {
        QMessageBox::information(this, "Error", "Name is empty");
        return;
    }
    size_t id;
    bool exist = findByName(name, id);
    if (exist) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Are you sure", "Do you want to remove this entry?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            data.erase(data.begin() + id);
            ui->lineEditRemoveName->clear();
            filterData();
        }
    } else {
        QMessageBox::information(this, "Error", "Entry does not exist");
    }
}

void JAPM::on_checkBoxTags_stateChanged(int arg1)
{
    /* idk what is arg1, it was added automatically */
    (void)arg1;
    filterData();
}

void JAPM::on_pushButtonSort_clicked()
{
    std::sort(data.begin(), data.end());
    filterData();
}

void JAPM::filterData() {
    std::string pattern = ui->lineEditSearch->text().toStdString();
    if (!pattern.empty()) {
        bool caseSenstitive = ui->checkBoxCaseSensitive->isChecked();
        pattern_text_t pt(pattern, caseSenstitive);
        bool searchName = ui->radioButtonName->isChecked();
        visible.clear();
        if (searchName) {
            for (size_t i = 0; i < data.size(); ++i) {
                if (pt.searchIn(data[i].name)) {
                    visible.push_back(i);
                }
            }
        } else {
            for (size_t i = 0; i < data.size(); ++i) {
                for (const std::string & tag : data[i].tags) {
                    if (pt.searchIn(tag)) {
                        visible.push_back(i);
                        break;
                    }
                }
            }
        }
    }
    displayData();
}

void JAPM::on_lineEditSearch_textEdited(const QString &arg1)
{
    /* idk what is arg1, it was added automatically */
    (void)arg1;
    visible.clear();
    filterData();
}

void JAPM::on_radioButtonName_clicked()
{
    filterData();
}

void JAPM::on_radioButtonTags_clicked()
{
    filterData();
}

void JAPM::on_checkBoxCaseSensitive_stateChanged(int arg1)
{
    /* idk what is arg1, it was added automatically */
    (void)arg1;
    filterData();
}
