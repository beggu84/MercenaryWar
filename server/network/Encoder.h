#pragma once

#include <openssl/aes.h>
#include <string>

using byte = unsigned char;

class Encoder
{
public:
	void GenerateAesKey(const std::string& keyStr);

	bool Decode(const std::string& src, std::string& dest);
	bool Encode(const std::string& src, std::string& dest);

private:
	//std::string Decompress(const std::string& str);
	bool DecryptText(const std::string& cipheredText, std::string& decipheredText) const;
	void DecryptBlock(byte* cipheredData, byte* decipheredData) const;

	bool EncryptText(const std::string& plainText, std::string& cipheredText)  const;
	void EncryptBlock(byte* plainData, byte* cipheredData, size_t length) const;
	//std::string Compress(const std::string& str);

private:
	AES_KEY _encKey, _decKey;
};
