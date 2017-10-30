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

struct SignalBitmask {
	SignalBitmask() :
	bitmask(0b111),
	name("blubb")
	{
	}
	SignalBitmask(const int bitmask2, std::string name) :
	bitmask(bitmask2),
	name(name)
	{
		LOG_SCOPE
	}
	~SignalBitmask(){
		LOG_SCOPE
	}
	const int bitmask;
	std::string name;
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

	static SignalBitmask BUTTON_START_PUSHED;
	static SignalBitmask BUTTON_STOP_PULLED;
	static SignalBitmask BUTTON_RESET_PUSHED;
	static SignalBitmask BUTTON_E_STOP_PULLED;
	static SignalBitmask LIGHT_BARRIER_INPUT_NOT_INTERRUPTED;
	static SignalBitmask LIGHT_BARRIER_HEIGHT_NOT_INTERRUPTED;
	static SignalBitmask SENSOR_HEIGHT_MATCH;
	static SignalBitmask LIGHT_BARRIER_SWITCH_NOT_INTERRUPTED;
	static SignalBitmask SENSOR_METAL_MATCH;
	static SignalBitmask LIGHT_BARRIER_SLIDE_NOT_INTERRUPTED;
	static SignalBitmask SENSOR_SWITCH_IS_OPEN;
	static SignalBitmask LIGHT_BARRIER_OUTPUT_NOT_INTERRUPTED;

};

} /* io */
} /* hal */

#endif /* ASYNCCHANNEL_H_ */
