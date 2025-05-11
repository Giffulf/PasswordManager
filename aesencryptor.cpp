#include "aesencryptor.h"
#include <cstring>
#include <stdexcept>

AESEncryptor::AESEncryptor() : cipher_ctx_(nullptr) {
    initKeyAndIV(); // Генерируем ключ и вектор инициализации
    cipher_ctx_ = EVP_CIPHER_CTX_new();
    if (!cipher_ctx_) {
        throw std::runtime_error("Ошибка выделения памяти для контекста шифрования.");
    }
}

AESEncryptor::~AESEncryptor() {
    if (cipher_ctx_) {
        EVP_CIPHER_CTX_free(cipher_ctx_);
    }
}

void AESEncryptor::initKeyAndIV() {
    // Простой пример ключа и IV
    memset(key_, 0xFF, sizeof(key_));       // Заполняем ключ произвольными значениями
    memset(iv_, 0xAB, sizeof(iv_));         // Заполняем IV произвольными значениями
}

std::string AESEncryptor::encrypt(const std::string &data) {
    // Размер буферов для вывода
    int block_size = EVP_CIPHER_block_size(EVP_aes_256_cbc());
    int bufsize = ((data.size() / block_size) + 1) * block_size;
    unsigned char *outbuf = new unsigned char[bufsize];

    // Настраиваем контекст шифрования
    if (!EVP_EncryptInit_ex(cipher_ctx_, EVP_aes_256_cbc(), nullptr, key_, iv_)) {
        delete[] outbuf;
        throw std::runtime_error("Ошибка инициализации шифрования.");
    }

    // Вычисляем длину выходящего буфера
    int len;
    if (!EVP_EncryptUpdate(cipher_ctx_, outbuf, &len, reinterpret_cast<const unsigned char *>(data.data()), data.size())) {
        delete[] outbuf;
        throw std::runtime_error("Ошибка обновления состояния шифрования.");
    }

    // Завершаем процесс шифрования
    int finallen;
    if (!EVP_EncryptFinal_ex(cipher_ctx_, outbuf + len, &finallen)) {
        delete[] outbuf;
        throw std::runtime_error("Ошибка завершения процесса шифрования.");
    }

    // Формируем строку результата
    std::string result(reinterpret_cast<char *>(outbuf), len + finallen);
    delete[] outbuf;
    return result;
}

std::string AESEncryptor::decrypt(const std::string &encryptedData) {
    // Буферы для выхода
    int block_size = EVP_CIPHER_block_size(EVP_aes_256_cbc());
    int bufsize = ((encryptedData.size() / block_size) + 1) * block_size;
    unsigned char *outbuf = new unsigned char[bufsize];

    // Устанавливаем контекст дешифрования
    if (!EVP_DecryptInit_ex(cipher_ctx_, EVP_aes_256_cbc(), nullptr, key_, iv_)) {
        delete[] outbuf;
        throw std::runtime_error("Ошибка инициализации дешифрования.");
    }

    // Процесс декодирования
    int len;
    if (!EVP_DecryptUpdate(cipher_ctx_, outbuf, &len, reinterpret_cast<const unsigned char *>(encryptedData.data()), encryptedData.size())) {
        delete[] outbuf;
        throw std::runtime_error("Ошибка обновления состояния дешифрования.");
    }

    // Завершение процесса
    int finallen;
    if (!EVP_DecryptFinal_ex(cipher_ctx_, outbuf + len, &finallen)) {
        delete[] outbuf;
        throw std::runtime_error("Ошибка завершения процесса дешифрования.");
    }

    // Создаем результирующую строку
    std::string result(reinterpret_cast<char *>(outbuf), len + finallen);
    delete[] outbuf;
    return result;
}

