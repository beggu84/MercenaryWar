#pragma once

#include <string>

class HttpDownloader
{
public:
	static std::string Download(const std::string& urlWithParam);
	static std::string DownloadWithParam(const std::string& url, const std::string& param);
};
