//---------------------------------------------------------------------------------------
// Encryption.h
// 
// This is the header file of the Encryption class.
// 
//---------------------------------------------------------------------------------------
#pragma once

//---------------------------------------------------------------------------------------
//
// Include files of general use libraries
//
#include <Windows.h>
#include <openssl/evp.h>
#include <openssl/aes.h>

//---------------------------------------------------------------------------------------
//
// Class definition: Encryption
//
class Encryption
{
public:
    //-----------------------------------------------------------------------------------
    //
    // Constructor and destructor
    Encryption(const unsigned char* key, const unsigned char* iv);
    ~Encryption();

    //-----------------------------------------------------------------------------------
    // Public functions of the Encryption class
    //
    void Encrypt(const unsigned char* plaintext, int plaintext_len, unsigned char* ciphertext, int& ciphertext_len);
    void Decrypt(const unsigned char* ciphertext, int ciphertext_len, unsigned char* plaintext, int& plaintext_len);

private:
    const unsigned char* m_key;
    const unsigned char* m_iv;
    EVP_CIPHER_CTX* m_encryptCtx;
    EVP_CIPHER_CTX* m_decryptCtx;
};
