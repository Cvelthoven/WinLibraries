#pragma once
#include <Windows.h>
#include <openssl/evp.h>
#include <openssl/aes.h>

class Encryption
{
public:
    Encryption(const unsigned char* key, const unsigned char* iv);
    ~Encryption();
    void Encrypt(const unsigned char* plaintext, int plaintext_len, unsigned char* ciphertext, int& ciphertext_len);
    void Decrypt(const unsigned char* ciphertext, int ciphertext_len, unsigned char* plaintext, int& plaintext_len);

private:
    const unsigned char* m_key;
    const unsigned char* m_iv;
    EVP_CIPHER_CTX* m_encryptCtx;
    EVP_CIPHER_CTX* m_decryptCtx;
};
