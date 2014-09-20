#ifndef STREAM_SERVER_H
#define STREAM_SERVER_H

#include <boost/asio.hpp>
#include <vector>
#include <thread>
#include <memory>
#include <set>
#include <sstream>

#include "serverConnection.h"
#include "common/timeUtils.h"
#include "common/queue.h"
#include "common/message.h"
#include "common/headerMessage.h"
#include "common/sampleFormat.h"


using boost::asio::ip::tcp;
typedef std::shared_ptr<tcp::socket> socket_ptr;
using namespace std;



class StreamServer
{
public:
	StreamServer(unsigned short port);
	void send(shared_ptr<BaseMessage> message);

	void start();
	void stop();

private:
	void acceptor();
	set<shared_ptr<ServerSession>> sessions;
	boost::asio::io_service io_service_;
	unsigned short port_;
	shared_ptr<HeaderMessage> headerChunk;
	shared_ptr<SampleFormat> sampleFormat;
	thread* acceptThread;
};


class ServerException : public std::exception
{
public:
	ServerException(const std::string& what) : what_(what)
	{
	}

	virtual ~ServerException() throw()
	{
	}

	virtual const char* what() const throw()
	{
		return what_.c_str();
	}

private:
	std::string what_;
};


#endif


