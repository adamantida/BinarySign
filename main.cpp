#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <locale>
#include "base64.h"

// Функция для добавления подписи к файлу
void add_signature(const std::string& input_file, const std::string& output_file, const std::string& comment) {
    std::ifstream infile(input_file, std::ios::binary);
    std::ofstream outfile(output_file, std::ios::binary);

    if (!infile) {
        throw std::runtime_error("Error opening input file: " + input_file);
    }
    if (!outfile) {
        throw std::runtime_error("Error opening output file: " + output_file);
    }

    // Копируем содержимое исходного файла
    outfile << infile.rdbuf();

    // Шифруем комментарий
    char* encoded_comment = base64_encode(const_cast<char*>(comment.c_str()));

    // Добавляем подпись
    std::string signature = "SignatureSertificationLSD: " + std::string(encoded_comment);
    outfile.write(signature.c_str(), signature.size());

    free(encoded_comment);
}

// Функция для проверки подписи в файле
void verify_signature(const std::string& file) {
    std::ifstream infile(file, std::ios::binary);
    if (!infile) {
        throw std::runtime_error("Error opening a file for verification: " + file);
    }

    std::string buffer((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());

    std::string signature_tag = "SignatureSertificationLSD: ";
    auto pos = buffer.find(signature_tag);
    if (pos != std::string::npos) {
        std::string encoded_comment = buffer.substr(pos + signature_tag.length());
        char* decoded_comment = base64_decode(const_cast<char*>(encoded_comment.c_str()));

        std::cout << "Found a signature: " << decoded_comment << std::endl; // Вывод декодированной подписи

        free(decoded_comment);
    } else {
        std::cout << "Signature not found." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    std::locale::global(std::locale("ru_RU.UTF-8"));

    if (argc < 3) {
        std::cerr << "Use: " << argv[0] << " [-i <input_file>] [-o <output_file>] [-c <comment>] [-v <verify_file>]" << std::endl;
        return 1;
    }

    std::string input_file, output_file, comment;
    bool verify_mode = false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            if (i + 1 < argc) {
                input_file = argv[++i];
            } else {
                std::cerr << "No input file name specified!" << std::endl;
                return 1;
            }
        } else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                output_file = argv[++i];
            } else {
                std::cerr << "Output file name is not specified!" << std::endl;
                return 1;
            }
        } else if (strcmp(argv[i], "-c") == 0) {
            if (i + 1 < argc) {
                comment = argv[++i];
            } else {
                std::cerr << "No comment specified!" << std::endl;
                return 1;
            }
        } else if (strcmp(argv[i], "-v") == 0) {
            if (i + 1 < argc) {
                input_file = argv[++i];
                verify_mode = true;
            } else {
                std::cerr << "No filename specified for checking!" << std::endl;
                return 1;
            }
        }
    }

    try {
        if (verify_mode) {
            verify_signature(input_file);
        } else if (!input_file.empty() && !output_file.empty() && !comment.empty()) {
            add_signature(input_file, output_file, comment);
        } else {
            std::cerr << "Insufficient arguments to perform the operation!" << std::endl;
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
