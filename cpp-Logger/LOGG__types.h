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



//TODO: Add error enum



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

	virtual int critical(const string) const = 0;
	virtual int error(const string) const = 0;
	virtual int warning(const string) const = 0;
	virtual int info(const string) const = 0;
	virtual int debug(const string) const = 0;

	virtual LogLevel get_level(void) const = 0;
	virtual int set_level(const LogLevel) = 0;

	virtual ostream* get_stream_ptr(void) const = 0;

protected:
	ostream* stream_ptr_;
	LogLevel log_level_;

	virtual int log_(const LogLevel, const string) const = 0;
};



class LoggerBase : public LoggerInterface {
public:
	LoggerBase(void);
	LoggerBase(const LogLevel);
	LoggerBase(const LogLevel, ostream*);
	virtual ~LoggerBase(void) = 0;

	int critical(const string) const;
	int error(const string) const;
	int warning(const string) const;
	int info(const string) const;
	int debug(const string) const;

	LogLevel get_level(void) const;
	int set_level(const LogLevel);

	ostream* get_stream_ptr(void) const;

protected:
	int log_(const LogLevel, const string) const;
};



class NullLogger : public LoggerBase {
public:
	NullLogger(void);
	NullLogger(const NullLogger&);
	~NullLogger(void);

	int set_level(const LogLevel);
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
