/*
 * AsyncChannel.cpp
 *
 *  Created on: 15.05.2017
 *      Author: aca216
 */

#include "AsyncChannel.h"
#include "Header.h"

#include <sys/neutrino.h>
#include <string>

#include <thread>


using namespace std;

namespace hal {
namespace io {

AsyncChannel::AsyncChannel() {
	//creating Channel
	channelId = ChannelCreate_r(0);
	if(channelId<0){
		LOG_ERROR<<"Fail Channel create: "<<channelId;
		exit(EXIT_FAILURE);
	}

	//creating connection to Channel
	connectionId = ConnectAttach_r(0, 0, channelId, 0, 0);
	if(connectionId<0){
		LOG_ERROR<<"Fail Channel create: "<<connectionId;
		exit(EXIT_FAILURE);
	}

	//LOG_HAL("Channel created: " + to_string(channelId) + " ( con: " + to_string(connectionId)+ ")");
}

AsyncChannel::~AsyncChannel() {
	ConnectDetach(connectionId);
	ChannelDestroy(channelId);

	//LOG_HAL("Channel destroyed");
}

AsyncMsg AsyncChannel::getNextMessage(){
	AsyncMsg msg;
	struct _pulse pulse;

	//wait for next message
	int ret = MsgReceivePulse_r(channelId, &pulse, sizeof(pulse), NULL);
	if(ret < 0){
		LOG_ERROR<<"Fail MsgReceivePulse: "<<ret;
		exit(EXIT_FAILURE);
	}

	//put data in own structure
	msg.type = pulse.code;
	msg.value = pulse.value.sival_int;

	return msg;
}

void AsyncChannel::sendMessage(AsyncMsg msg){
	//send message to channel via connectionId
    int ret = MsgSendPulse_r(
		connectionId,
		sched_get_priority_max(0),
    	msg.type,
		msg.value );
   	if(ret < 0){
   		LOG_ERROR<<"Fail MsgReceivePulse: "<<ret;
   		exit(EXIT_FAILURE);
   	}
}

int AsyncChannel::getConnectionId(){
	return connectionId;
}

AsyncChannel& AsyncChannel::getChannel(){
	static AsyncChannel instance;
	return instance;
}

} /* io */
} /* hal */
