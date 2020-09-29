#pragma once


#include <chrono>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <windows.h>


namespace Debug {

	inline std::tm localtime_xp(std::time_t timer) {
		std::tm bt{};
#if defined(__unix__)
		localtime_r(&timer, &bt);
#elif defined(_MSC_VER)
		localtime_s(&bt, &timer);
#else
		static std::mutex mtx;
		std::lock_guard<std::mutex> lock(mtx);
		bt = *std::localtime(&timer);
#endif
		return bt;
	}

	// default = "YYYY-MM-DD HH:MM:SS"
	inline std::string time_stamp(const std::string& fmt = "%F %T") {
		auto bt = localtime_xp(std::time(0));
		char buf[64];
		return { buf, std::strftime(buf, sizeof(buf), fmt.c_str(), &bt) };
	}

	std::string addressOf(const void* inst) {
		std::ostringstream _s;
		_s << &inst;
		return _s.str();
	}

	void log(const std::wstring& message) {
		log(message.c_str());
	}

	//Logs a string to an output log.txt file
	void log(const std::string& message) {
		//Get the log file
		WCHAR path[MAX_PATH];
		GetModuleFileNameW(nullptr, path, MAX_PATH);
		std::wstring _path{ path };
		_path = _path.substr(0, _path.find_last_of(L"\\/") + 1);
		std::ofstream _file(_path + L"log.txt", std::ios::app);
		if (_file.is_open()) {
			_file << time_stamp() << "\t" << message << std::endl;

			_file.close();
		}
	}
}