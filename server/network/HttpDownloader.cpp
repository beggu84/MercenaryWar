#include "HttpDownloader.h"

#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/curlbuild.h>
#include <sstream>
#include <iostream>

using namespace std;

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
	string data((const char*)ptr, (size_t)size * nmemb);
	*((stringstream*)stream) << data << endl;
	return size * nmemb;
}

string HttpDownloader::Download(const string& urlWithParam)
{
	CURL* curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL, urlWithParam.c_str());
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1);
	//curl_easy_setopt(curl, CURLOPT_AUTOREFERER, 1L);
	curl_easy_setopt(curl, CURLOPT_HEADER, 0L);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);
	std::stringstream out;
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);

	CURLcode res = curl_easy_perform(curl);

	if (res != CURLE_OK)
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

	curl_easy_cleanup(curl);

	return out.str();
}

string HttpDownloader::DownloadWithParam(const string& url, const string& params)
{
	CURL* curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1);
	curl_easy_setopt(curl, CURLOPT_HEADER, 0L);
	curl_easy_setopt(curl, CURLOPT_POST, 1L);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, params.size());
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params.data());
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30L);
	std::stringstream out;
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);

	CURLcode res = curl_easy_perform(curl);

	if (res != CURLE_OK)
		fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

	curl_easy_cleanup(curl);

	return out.str();
}
