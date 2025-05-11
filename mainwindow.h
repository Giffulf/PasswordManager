#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QVector>
#include "passwordrecord.h"
#include "aesencryptor.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_addButton_clicked();      // Добавляет новую запись пароля
    void on_removeButton_clicked();   // Удаляет выбранную запись пароля
    void on_editButton_clicked();     // Редактирует существующую запись пароля
    void on_searchField_textChanged(const QString &filter); // Фильтрует записи по введенному фильтру


private:
    Ui::MainWindow *ui;
    QVector<PasswordRecord*> records; // Контейнер хранит указатели на объекты типа PasswordRecord (пароли пользователей)
    AESEncryptor aes;        // Объект для шифрования данных (AES-шифрование)

    // Вспомогательные методы
    void updateUI(); // Метод обновляет интерфейс
    void clearInputFields(); // Очищает поля ввода новой записи
};

#endif // MAINWINDOW_H
