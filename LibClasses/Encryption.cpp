#include "Encryption.h"
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <cstring>

Encryption::Encryption(const unsigned char* key, const unsigned char* iv)
    : m_key(key), m_iv(iv)
{
    m_encryptCtx = EVP_CIPHER_CTX_new();
    m_decryptCtx = EVP_CIPHER_CTX_new();

    EVP_EncryptInit_ex(m_encryptCtx, EVP_aes_256_cbc(), NULL, m_key, m_iv);
    EVP_DecryptInit_ex(m_decryptCtx, EVP_aes_256_cbc(), NULL, m_key, m_iv);
}

Encryption::~Encryption()
{
    EVP_CIPHER_CTX_free(m_encryptCtx);
    EVP_CIPHER_CTX_free(m_decryptCtx);
}

void Encryption::Encrypt(const unsigned char* plaintext, int plaintext_len, unsigned char* ciphertext, int& ciphertext_len)
{
    int len;
    EVP_EncryptInit_ex(m_encryptCtx, NULL, NULL, NULL, NULL);
    EVP_EncryptUpdate(m_encryptCtx, ciphertext, &len, plaintext, plaintext_len);
    ciphertext_len = len;
    EVP_EncryptFinal_ex(m_encryptCtx, ciphertext + len, &len);
    ciphertext_len += len;
}

void Encryption::Decrypt(const unsigned char* ciphertext, int ciphertext_len, unsigned char* plaintext, int& plaintext_len)
{
    int len;
    EVP_DecryptInit_ex(m_decryptCtx, NULL, NULL, NULL, NULL);
    EVP_DecryptUpdate(m_decryptCtx, plaintext, &len, ciphertext, ciphertext_len);
    plaintext_len = len;
    EVP_DecryptFinal_ex(m_decryptCtx, plaintext + len, &len);
    plaintext_len += len;
}
