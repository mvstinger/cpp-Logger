/*
 * LOGG__types.cc
 *
 *  Created on: Nov 13, 2016
 *      Author: mvstinger
 */



#include "../LOGG__types.h"



namespace Logger {



LogLevel LOGG__DEFAULT_LOG_LEVEL = LOG_DEBUG;



LoggerInterface::LoggerInterface(void) :
		ostream_ptr_(NULL),
		log_level_(LOGG__DEFAULT_LOG_LEVEL) {};

LoggerInterface::LoggerInterface(const LogLevel lvl) :
		ostream_ptr_(NULL),
		log_level_(lvl) {};

LoggerInterface::LoggerInterface(const LogLevel lvl, ostream* ptr) :
		ostream_ptr_(ptr),
		log_level_(lvl) {};

//LoggerInterface::~LoggerInterface(void) {};



LoggerBase::LoggerBase(void) {};

LoggerBase::LoggerBase(const LogLevel lvl) :
		LoggerInterface(lvl) {};

LoggerBase::LoggerBase(const LogLevel lvl, ostream* ptr) :
		LoggerInterface(lvl, ptr) {};

//LoggerBase::~LoggerBase(void) {};

int LoggerBase::critical(const string msg) const {
	int error_state = 0;
	this->log_(LOG_CRITICAL, msg);
	return error_state;
}

int LoggerBase::error(const string msg) const {
	int error_state = 0;
	this->log_(LOG_ERROR, msg);
	return error_state;
}

int LoggerBase::warning(const string msg) const {
	int error_state = 0;
	this->log_(LOG_WARNING, msg);
	return error_state;
}

int LoggerBase::info(const string msg) const {
	int error_state = 0;
	this->log_(LOG_INFO, msg);
	return error_state;
}

int LoggerBase::debug(const string msg) const {
	int error_state = 0;
	this->log_(LOG_DEBUG, msg);
	return error_state;
}

LogLevel LoggerBase::get_level(void) const {
	return this->log_level_;
}

int LoggerBase::set_level(const LogLevel lvl) {
	int error_state = 0;
	this->log_level_ = lvl;
	return error_state;
}

int LoggerBase::log_(const LogLevel lvl, const string msg) const {
	int error_state = 0;
	if(lvl >= this->log_level_) {
		 *(this->ostream_ptr_) << now_string() << "\t" << to_string(lvl) << "\t" << msg << std::endl;
	}
	return error_state;
}



NullLogger::NullLogger(void) :
		LoggerBase(LOG_SILENT) {};

NullLogger::~NullLogger(void) {};

//	Do not allow change of log level (this hides parent class method)
int NullLogger::set_level(const LogLevel irrelevant) { return 1; }



ConsoleLogger::ConsoleLogger(void) :
		LoggerBase(LOGG__DEFAULT_LOG_LEVEL, (ostream*)stdout) {};

ConsoleLogger::ConsoleLogger(const LogLevel lvl) :
		LoggerBase(lvl, (ostream*)stdout) {};

ConsoleLogger::~ConsoleLogger(void) {};



FileLogger::FileLogger(const string filepath) {
	this->ostream_target_ = ofstream(filepath.c_str());
	this->log_level_ = LOGG__DEFAULT_LOG_LEVEL;
	this->ostream_ptr_ = &(this->ostream_target_);
}

FileLogger::FileLogger(const LogLevel lvl, const string filepath) {
	this->ostream_target_ = ofstream(filepath.c_str());
	this->log_level_ = lvl;
	this->ostream_ptr_ = &(this->ostream_target_);
}

FileLogger::~FileLogger(void) {
	this->ostream_ptr_ = NULL;
	this->ostream_target_.close();
}



string now_string(void) {
	return string("YYYYmmdd_HHMMSS");
}



string to_string(const LogLevel lvl) {
	switch(lvl) {
	case LOG_SILENT:
		return "SILENT";
	case LOG_CRITICAL:
		return "CRITICAL";
	case LOG_ERROR:
		return "ERROR";
	case LOG_WARNING:
		return "WARNING";
	case LOG_INFO:
		return "INFO";
	case LOG_DEBUG:
		return "DEBUG";
	default:
		return "UNK";
	}
}



};
