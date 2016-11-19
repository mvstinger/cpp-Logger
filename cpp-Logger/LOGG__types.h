/*
 * LOGG_types.h
 *
 *  Created on: Nov 13, 2016
 *      Author: mvstinger
 */

#ifndef LOGG__TYPES_H_
#define LOGG__TYPES_H_



#include <iostream>
#include <ostream>
#include <string>



using std::string;
using std::ostream;
using std::ofstream;



namespace Logger {



enum LogError {
	NO_ERROR = 0,
	UNK_ERROR = 1,
	CANNOT_SET_LOG_LEVEL = 2
};



enum LogLevel {
	LOG_SILENT = 100,
	LOG_CRITICAL = 60,
	LOG_ERROR = 50,
	LOG_WARNING = 40,
	LOG_INFO = 30,
	LOG_DEBUG = 20
};



string now_string(void);
string to_string(LogLevel);



class LoggerInterface {
public:
	LoggerInterface(void);
	LoggerInterface(const LogLevel);
	LoggerInterface(const LogLevel, ostream*);
	virtual ~LoggerInterface(void) = 0;

	virtual LogError critical(const string) const = 0;
	virtual LogError error(const string) const = 0;
	virtual LogError warning(const string) const = 0;
	virtual LogError info(const string) const = 0;
	virtual LogError debug(const string) const = 0;

	virtual LogLevel get_level(void) const = 0;
	virtual LogError set_level(const LogLevel) = 0;

	virtual ostream* get_stream_ptr(void) const = 0;

protected:
	ostream* stream_ptr_;
	LogLevel log_level_;

	virtual LogError log_(const LogLevel, const string) const = 0;
};



class LoggerBase : public LoggerInterface {
public:
	LoggerBase(void);
	LoggerBase(const LogLevel);
	LoggerBase(const LogLevel, ostream*);
	virtual ~LoggerBase(void) = 0;

	LogError critical(const string) const;
	LogError error(const string) const;
	LogError warning(const string) const;
	LogError info(const string) const;
	LogError debug(const string) const;

	LogLevel get_level(void) const;
	LogError set_level(const LogLevel);

	ostream* get_stream_ptr(void) const;

protected:
	LogError log_(const LogLevel, const string) const;
};



class NullLogger : public LoggerBase {
public:
	NullLogger(void);
	NullLogger(const NullLogger&);
	~NullLogger(void);

	LogError set_level(const LogLevel);
};



class ConsoleLogger : public LoggerBase {
public:
	ConsoleLogger(void);
	ConsoleLogger(const ConsoleLogger&);
	ConsoleLogger(const LogLevel);
	~ConsoleLogger(void);
};



class FileLogger : public LoggerBase {
public:
	FileLogger(const string);
	FileLogger(const LogLevel, const string);
	~FileLogger(void);

private:
	ofstream stream_target_;
};





}



#endif /* LOGG__TYPES_H_ */
