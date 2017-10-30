/*
 * AsyncChannel.h
 *
 *  Created on: 15.05.2017
 *      Author: aca216
 */

#ifndef ASYNCCHANNEL_H_
#define ASYNCCHANNEL_H_

#include <string>
#include "Header.h"

struct AsyncMsg {
	char type;
	int value;
};

namespace hal {
namespace io {

class AsyncChannel {
private:
	int channelId;
	int connectionId;
	AsyncChannel();

	//avoid copying of singletons
	AsyncChannel& operator=(const AsyncChannel&);
	AsyncChannel(const AsyncChannel&);

public:

	/*
	 * @brief: Destructor
	 * @after: all bound ressources of this channel are being freed
	 */
	virtual ~AsyncChannel();

	/*
	 * @brief: gets Instance (if needed creates multiton object and) returns it
	 */
	static AsyncChannel& getChannel();

	/*
	 * @brief: waits(blocked) for next Message and returns it
	 * @return: received Message
	 */
	AsyncMsg getNextMessage();

	/*
	 * @brief: sends Message to Channel via single Connection
	 * @param: msg to send
	 */
	void sendMessage(AsyncMsg msg);

	/*
	 * @brief: returns connection id to channel
	 */
	int getConnectionId();

};

} /* io */
} /* hal */

#endif /* ASYNCCHANNEL_H_ */
