# Password Manager 🔒  

**Secure password storage application**  
*Developed in Qt Creator using C++*  

[![Qt](https://img.shields.io/badge/Qt-5.15%2B-green?logo=qt)](https://www.qt.io/)  
[![C++](https://img.shields.io/badge/C++-17-blue?logo=c%2B%2B)](https://isocpp.org/)  
[![License](https://img.shields.io/badge/license-MIT-green)](LICENSE)  
[![Build](https://img.shields.io/badge/build-QMake-blue)](https://doc.qt.io/qt-6/qmake-manual.html)  

## 📌 About  

Password Manager is a desktop application that provides:  
🔐 Secure encrypted password storage  
🔑 Strong password generation  
🛡 Master password protection  

## 🚀 Getting Started  

### Prerequisites  
- Qt 5.15+  
- C++17 compatible compiler  

### Building from Source  
bash
git clone https://github.com/Giffulf/PasswordManager.git
cd PasswordManager

# Build with qmake
qmake PasswordManager.pro
make

# Run the application
./PasswordManager

## 🛠 Technologies  

| Component       | Technologies Used               |
|----------------|--------------------------------|
| GUI Framework  | Qt Widgets                     |
| Language       | C++17                          |
| Cryptography   | Qt Crypto (AES-256)            |
| Database       | SQLite                         |
| Build System   | QMake                          |

## 🔐 Security Features  

- AES-256 encryption for all stored data  
- PBKDF2 hashing for master password  
