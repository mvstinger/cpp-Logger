/*
 * LOGG_types.h
 *
 *  Created on: Nov 13, 2016
 *      Author: mvstinger
 */

#ifndef LOGG_TYPES_H_
#define LOGG_TYPES_H_

#include <fstream>
//#include <cstdio>
#include <string>



namespace Logger {



using std::string;
using std::ostream;
using std::ofstream;


class LoggerInterface;
class LoggerBase;
class NullLogger;
class ConsoleLogger;
class FileLogger;



enum LogLevel {
	LOG_SILENT = 100,
	LOG_CRITICAL = 60,
	LOG_ERROR = 50,
	LOG_WARNING = 40,
	LOG_INFO = 30,
	LOG_DEBUG = 20
};

LogLevel LOGG__DEFAULT_LOG_LEVEL = LOG_DEBUG;



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

	virtual LogLevel get_level(void) const;
	virtual int set_level(const LogLevel);

protected:
	ostream* ostream_ptr_;
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

protected:
	int log_(const LogLevel, const string) const;
};



class NullLogger : public LoggerBase {
public:
	NullLogger(void);
	~NullLogger(void);

	int set_level(const LogLevel);
};



class ConsoleLogger : LoggerBase {
public:
	ConsoleLogger(void);
	ConsoleLogger(LogLevel);
	~ConsoleLogger(void);
};



class FileLogger : LoggerBase {
public:
	FileLogger(const string);
	FileLogger(const LogLevel, const string);
	~FileLogger(void);

private:
	ofstream ostream_target_;
};





}



#endif /* LOGG_TYPES_H_ */
