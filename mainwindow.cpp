#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Настройка соединений сигналов и слотов
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(onAddButtonClicked()));
    connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(onRemoveButtonClicked()));
    connect(ui->editButton, SIGNAL(clicked()), this, SLOT(onEditButtonClicked()));
    connect(ui->searchField, SIGNAL(textChanged(QString)), this, SLOT(onSearchTextChanged(QString)));

    updateUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Добавляем новую запись пароля
void MainWindow::on_addButton_clicked()
{
    QString siteName = ui->siteNameEdit->text().trimmed();
    QString login = ui->loginEdit->text().trimmed();
    QString pass = ui->passwordEdit->text().trimmed();

    if (!siteName.isEmpty() && !login.isEmpty() && !pass.isEmpty()) {
        PasswordRecord* newRecord = new PasswordRecord(siteName, login, pass.toUtf8());
        records.append(newRecord);
        updateUI();
        clearInputFields();
    }
}

// Обновляем представление списка записей
void MainWindow::updateUI() {
    ui->listWidget->clear();
    foreach(PasswordRecord* record, records) {
        QString displayText = QString("%1 (%2)").arg(record->getSiteName()).arg(record->getLogin());
        QListWidgetItem* item = new QListWidgetItem(displayText);
        ui->listWidget->addItem(item);
    }
}

// Очистка полей ввода после сохранения
void MainWindow::clearInputFields() {
    ui->siteNameEdit->clear();
    ui->loginEdit->clear();
    ui->passwordEdit->clear();
}

// Удаляем выбранную запись
void MainWindow::on_removeButton_clicked()
{
    QList<QListWidgetItem *> selectedItems = ui->listWidget->selectedItems();
    if(selectedItems.count() > 0){
        foreach(QListWidgetItem* item, selectedItems) {
            int index = ui->listWidget->row(item);
            delete records[index]; // Освобождаем память
            records.removeAt(index); // Убираем запись из массива
        }
        updateUI();
    }
}

// Редактирование выбранного элемента
void MainWindow::on_editButton_clicked()
{
    QList<QListWidgetItem *> selectedItems = ui->listWidget->selectedItems();
    if(selectedItems.count() > 0){
        int index = ui->listWidget->currentRow();
        PasswordRecord* rec = records.at(index);

        // Запрашиваем новые значения через диалоговые окна
        bool ok;
        QString newSiteName = QInputDialog::getText(this, "Редактировать сайт", "Название сайта:", QLineEdit::Normal, rec->getSiteName(), &ok);
        if(ok && !newSiteName.isEmpty()) { rec->setSiteName(newSiteName); }

        QString newLogin = QInputDialog::getText(this, "Редактировать логин", "Логин:", QLineEdit::Normal, rec->getLogin(), &ok);
        if(ok && !newLogin.isEmpty()) { rec->setLogin(newLogin); }

        QString newPassword = QInputDialog::getText(this, "Редактировать пароль", "Пароль:", QLineEdit::PasswordEchoOnEdit, "", &ok);
        if(ok && !newPassword.isEmpty()) {
            QByteArray encryptedPassword = QByteArray::fromStdString(aes.encrypt(newPassword.toUtf8().constData()));
            rec->setEncryptedPassword(encryptedPassword);
        }

        updateUI();
    }
}

// Реализация фильтра по сайтам
void MainWindow::on_searchField_textChanged(const QString &filter) {
    ui->listWidget->clear();
    foreach(PasswordRecord* record, records) {
        if(record->getSiteName().contains(filter, Qt::CaseInsensitive)) {
            QString displayText = QString("%1 (%2)").arg(record->getSiteName()).arg(record->getLogin());
            QListWidgetItem* item = new QListWidgetItem(displayText);
            ui->listWidget->addItem(item);
        }
    }
}
