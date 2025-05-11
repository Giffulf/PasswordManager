#include "passwordrecord.h"
#include "aesencryptor.h"

PasswordRecord::PasswordRecord(QString siteName, QString login, QByteArray password) :
    m_siteName(siteName),
    m_login(login)
{
    // Шифруем пароль с помощью AESEncryptor
    AESEncryptor aes;
    m_encryptedPassword = QByteArray::fromStdString(aes.encrypt(password.toStdString()));
}

QString PasswordRecord::getDecryptedPassword(AESEncryptor *aes) const {
    // Расшифровка пароля обратно в строку
    std::string decryptedPass = aes->decrypt(m_encryptedPassword.toStdString());
    return QString::fromStdString(decryptedPass);
}
