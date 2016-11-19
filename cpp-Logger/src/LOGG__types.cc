/*
 * LOGG__types.cc
 *
 *  Created on: Nov 13, 2016
 *      Author: mvstinger
 */



#include <iostream>
#include <fstream>
#include <ctime>
#include "../LOGG__types.h"



using std::cout;
using std::ostream;
using std::ofstream;



namespace Logger {



LogLevel LOGG__DEFAULT_LOG_LEVEL = LOG_WARNING;



LoggerInterface::LoggerInterface(void) :
		stream_ptr_(NULL),
		log_level_(LOGG__DEFAULT_LOG_LEVEL) {};

LoggerInterface::LoggerInterface(const LogLevel lvl) :
		stream_ptr_(NULL),
		log_level_(lvl) {};

LoggerInterface::LoggerInterface(const LogLevel lvl, ostream* ptr) :
		stream_ptr_(ptr),
		log_level_(lvl) {};

LoggerInterface::~LoggerInterface(void) {};



LoggerBase::LoggerBase(void) {};

LoggerBase::LoggerBase(const LogLevel lvl) :
		LoggerInterface(lvl) {};

LoggerBase::LoggerBase(const LogLevel lvl, ostream* ptr) :
		LoggerInterface(lvl, ptr) {};

LoggerBase::~LoggerBase(void) {};

LogError LoggerBase::critical(const string msg) const {
	LogError error_state = NO_ERROR;
	this->log_(LOG_CRITICAL, msg);
	return error_state;
}

LogError LoggerBase::error(const string msg) const {
	LogError error_state = NO_ERROR;
	this->log_(LOG_ERROR, msg);
	return error_state;
}

LogError LoggerBase::warning(const string msg) const {
	LogError error_state = NO_ERROR;
	this->log_(LOG_WARNING, msg);
	return error_state;
}

LogError LoggerBase::info(const string msg) const {
	LogError error_state = NO_ERROR;
	this->log_(LOG_INFO, msg);
	return error_state;
}

LogError LoggerBase::debug(const string msg) const {
	LogError error_state = NO_ERROR;
	this->log_(LOG_DEBUG, msg);
	return error_state;
}

LogLevel LoggerBase::get_level(void) const {
	return this->log_level_;
}

LogError LoggerBase::set_level(const LogLevel lvl) {
	LogError error_state = NO_ERROR;
	this->log_level_ = lvl;
	return error_state;
}

ostream* LoggerBase::get_stream_ptr(void) const {	return this->stream_ptr_; }

LogError LoggerBase::log_(const LogLevel lvl, const string msg) const {
	LogError error_state = NO_ERROR;
	if(lvl >= this->log_level_) {
		*(this->stream_ptr_) << now_string() << "\t" << to_string(lvl) << "\t" << msg << std::endl;
	}
	return error_state;
}



NullLogger::NullLogger(void) :
		LoggerBase(LOG_SILENT) {};

NullLogger::NullLogger(const NullLogger& that) :
		LoggerBase(LOG_SILENT) {};

NullLogger::~NullLogger(void) {};

//	Do not allow change of log level (this hides parent class method)
LogError NullLogger::set_level(const LogLevel irrelevant) { return CANNOT_SET_LOG_LEVEL; }



ConsoleLogger::ConsoleLogger(void) :
		LoggerBase(LOGG__DEFAULT_LOG_LEVEL, &cout) {};

ConsoleLogger::ConsoleLogger(const ConsoleLogger& that) :
		LoggerBase(that.get_level(), &cout) {};

ConsoleLogger::ConsoleLogger(const LogLevel lvl) :
		LoggerBase(lvl, &cout) {};

ConsoleLogger::~ConsoleLogger(void) {};



FileLogger::FileLogger(const string filepath) {
	this->stream_target_ = ofstream(filepath.c_str());
	this->log_level_ = LOGG__DEFAULT_LOG_LEVEL;
	this->stream_ptr_ = &(this->stream_target_);
}

FileLogger::FileLogger(const LogLevel lvl, const string filepath) {
	this->stream_target_ = ofstream(filepath.c_str(), std::ofstream::app);
	this->log_level_ = lvl;
	this->stream_ptr_ = &(this->stream_target_);
}

FileLogger::~FileLogger(void) {
	this->stream_ptr_ = NULL;
	this->stream_target_.close();
}



string now_string(void) {
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[30];

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer,30,"%Y%m%d_%H%M%S",timeinfo);
	std::string str(buffer);
	return str;
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
