#ifndef AESCRYPTOR_H
#define AESCRYPTOR_H

#include <string>
#include <openssl/evp.h>

class AESEncryptor {
public:
    AESEncryptor();              // Конструктор с ключом по умолчанию
    ~AESEncryptor();             // Освобождаем ресурсы

    // Методы шифрования и дешифровки
    std::string encrypt(const std::string &data);
    std::string decrypt(const std::string &encryptedData);

private:
    void initKeyAndIV();          // Генерация ключа и вектора инициализации
    EVP_CIPHER_CTX *cipher_ctx_;  // Контекст шифрования
    unsigned char key_[EVP_MAX_KEY_LENGTH]; // Ключ
    unsigned char iv_[EVP_MAX_IV_LENGTH];   // Вектор инициализации
};

#endif // AESCRYPTOR_H
