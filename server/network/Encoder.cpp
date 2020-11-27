#include "Encoder.h"

#include <vector>

//#include <boost/iostreams/filtering_streambuf.hpp>
//#include <boost/iostreams/copy.hpp>
//#include <boost/iostreams/filter/gzip.hpp>

#define AES_BIT 128

using namespace std;

void Encoder::GenerateAesKey(const string& keyStr)
{
	byte aesKeyBytes[AES_BLOCK_SIZE];
	memset(aesKeyBytes, 0, AES_BLOCK_SIZE);
	memcpy(aesKeyBytes, keyStr.data(), keyStr.length());

	//Printbytes(REST_SERVER_AES_1ST_KEY, aesKeyBytes, AES_BLOCK_SIZE);

	AES_set_encrypt_key(aesKeyBytes, AES_BIT, &_encKey);
	AES_set_decrypt_key(aesKeyBytes, AES_BIT, &_decKey);
}

void PrintBytes(const char *title, const void* data, int len)
{
	printf("%s : ", title);
	const byte * p = (const byte*)data;
	int i = 0;

	for (; i<len; ++i)
		printf("%02X ", *p++);
	//printf("%d ", *p++);

	printf("\n");
}

bool Encoder::Decode(const string& src, string& dest)
{
	//string cipheredText = Decompress(str);
	//if (bVersion)
	//	decipheredText = DecryptText(cipheredText, first_decKey);
	//else
	//	decipheredText = DecryptText(cipheredText, random_decKey);
	//return json::parse(decipheredText);

	string decipheredText;
	DecryptText(src, dest);

	return true;
}

//string WebServer::Decompress(const string& str)
//{
//	namespace bio = boost::iostreams;
//
//	stringstream compressed(str);
//	stringstream decompressed;
//
//	bio::filtering_streambuf<bio::input> out;
//	out.push(bio::gzip_decompressor());
//	out.push(compressed);
//	bio::copy(out, decompressed);
//
//	return decompressed.str();
//}

bool Encoder::DecryptText(const string& cipheredText, string& decipheredText) const
{
	//LOG_INFO("Start Decrypt");
	size_t segmentSize = cipheredText.length() / AES_BLOCK_SIZE;
	if (segmentSize * AES_BLOCK_SIZE < cipheredText.length())
		segmentSize++;
	decipheredText.resize(segmentSize*AES_BLOCK_SIZE, '\0');

	size_t byteCount = 0;
	while (cipheredText.length() > byteCount)
	{
		byte cipheredData[AES_BLOCK_SIZE];
		memset(cipheredData, 0, AES_BLOCK_SIZE);
		memcpy(cipheredData, cipheredText.data() + byteCount, AES_BLOCK_SIZE);

		//Printbytes("cipheredData", cipheredData, AES_BLOCK_SIZE);
		byte decipheredData[AES_BLOCK_SIZE];
		DecryptBlock(cipheredData, decipheredData);
		//Printbytes("decipheredData", decipheredData, AES_BLOCK_SIZE);

		memcpy(&(decipheredText[0]) + byteCount, decipheredData, AES_BLOCK_SIZE);

		byteCount += AES_BLOCK_SIZE;
	}
	decipheredText += '\0';

	return true;
}

void Encoder::DecryptBlock(byte* cipheredData, byte* decipheredData) const
{
	AES_decrypt(cipheredData, decipheredData, &_decKey);
}

bool Encoder::Encode(const string& src, string& dest)
{
	EncryptText(src, dest);

	//str = Compress(cipheredText);

	return true;
}

bool Encoder::EncryptText(const string& plainText, string& cipheredText) const
{
	//LOG_INFO("Start Encrypt: {0:s}", plainText);

	size_t segmentSize = plainText.length() / AES_BLOCK_SIZE;
	if (segmentSize * AES_BLOCK_SIZE < plainText.length())
		segmentSize++;
	cipheredText.resize(segmentSize*AES_BLOCK_SIZE, '\0');

	size_t byteCount = 0;
	while (plainText.length() > byteCount)
	{
		byte plainData[AES_BLOCK_SIZE];
		memset(plainData, 0, AES_BLOCK_SIZE);
		memcpy(plainData, plainText.data() + byteCount, AES_BLOCK_SIZE);

		size_t length = AES_BLOCK_SIZE;
		if (plainText.length() < byteCount + AES_BLOCK_SIZE)
			length = plainText.length() - byteCount;

		//Printbytes("plainData", plainData, AES_BLOCK_SIZE);
		byte cipheredData[AES_BLOCK_SIZE];
		EncryptBlock(plainData, cipheredData, length);
		//Printbytes("cipheredData", cipheredData, AES_BLOCK_SIZE);

		memcpy(&(cipheredText[0]) + byteCount, cipheredData, AES_BLOCK_SIZE);

		byteCount += AES_BLOCK_SIZE;
	}

	return true;
}

void Encoder::EncryptBlock(byte* plainData, byte* cipheredData, size_t length) const
{
	byte iv[AES_BLOCK_SIZE];
	memset(iv, 0x00, AES_BLOCK_SIZE);

	AES_cbc_encrypt(plainData, cipheredData, length, &_encKey, iv, AES_ENCRYPT);
}

//string Encoder::Compress(const string& str)
//{
//	namespace bio = boost::iostreams;
//
//	stringstream origin(str);
//
//	bio::filtering_streambuf<bio::input> out;
//	out.push(bio::gzip_compressor(bio::gzip_params(bio::gzip::best_compression)));
//	out.push(origin);
//
//	stringstream compressed;
//	bio::copy(out, compressed);
//
//	return compressed.str();
//}
