#ifndef PASSWORDRECORD_H
#define PASSWORDRECORD_H

#include <QString>
#include <QByteArray>

class AESEncryptor;

class PasswordRecord
{
public:
    // Конструктор с параметрами
    PasswordRecord(QString siteName, QString login, QByteArray password);

    // Геттеры для публичного доступа
    QString getSiteName() const { return m_siteName; }
    QString getLogin() const { return m_login; }
    QByteArray getEncryptedPassword() const { return m_encryptedPassword; }
    QString getDecryptedPassword(AESEncryptor* aes) const;

    // Сеттеры для изменения
    void setSiteName(const QString& value) { m_siteName = value; }
    void setLogin(const QString& value) { m_login = value; }
    void setEncryptedPassword(const QByteArray& value) { m_encryptedPassword = value; }

private:
    QString m_siteName;           // Название сайта
    QString m_login;              // Логин пользователя
    QByteArray m_encryptedPassword; // Зашифрованный пароль
};

#endif // PASSWORDRECORD_H

