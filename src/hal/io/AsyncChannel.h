/*
 * AsyncChannel.h
 *
 *  Created on: 20.10.2017
 *      Author: abj240
 */

#ifndef ASYNCCHANNEL_H_
#define ASYNCCHANNEL_H_

struct AsyncMsg {
	char type;
	int value;
};

namespace hal {
namespace io {

class AsyncChannel {

public:
	/*
	 * @brief: returns meyer's singleton
	 */
	static AsyncChannel& instance();

	/*
	 * @brief: Destructor.
	 * @after: bound resources of this channel are released
	 */
	virtual ~AsyncChannel();

	/*
	 * @brief: waits(blocked) for next message and returns it
	 * @return: received message (first in first out)
	 */
	AsyncMsg nextMessage();

	/*
	 * @brief: sends message to channel via single connection
	 * @param: message to send
	 */
	void sendMessage(AsyncMsg msg);

	/*
	 * @brief: returns connection id to channel
	 */
	int getConnectionId();

private:
	AsyncChannel();
	AsyncChannel(const AsyncChannel&);
	AsyncChannel& operator=(const AsyncChannel&);

	int channelId;
	int connectionId;

};

} /* io */
} /* hal */

#endif /* ASYNCCHANNEL_H_ */
