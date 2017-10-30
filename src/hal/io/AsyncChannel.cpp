/*
 * AsyncChannel.cpp
 *
 *  Created on: 15.05.2017
 *      Author: aca216
 */

#include "AsyncChannel.h"
#include "Header.h"

#include <sys/neutrino.h>
#include <thread>


using namespace std;

namespace hal {
namespace io {

SignalBitmask AsyncChannel::BUTTON_START_PUSHED =  SignalBitmask(0b00010000<<8, "BUTTON_START_PUSHED");
SignalBitmask AsyncChannel::BUTTON_STOP_PULLED =   SignalBitmask(0b00100000<<8, "BUTTON_STOP_PULLED");
SignalBitmask AsyncChannel::BUTTON_RESET_PUSHED =  SignalBitmask(0b01000000<<8, "BUTTON_RESET_PUSHED");
SignalBitmask AsyncChannel::BUTTON_E_STOP_PULLED = SignalBitmask(0b10000000<<8, "BUTTON_E_STOP_PULLED");
SignalBitmask AsyncChannel::LIGHT_BARRIER_INPUT_NOT_INTERRUPTED =  SignalBitmask(0b00000001, "LIGHT_BARRIER_INPUT_NOT_INTERRUPTED");
SignalBitmask AsyncChannel::LIGHT_BARRIER_HEIGHT_NOT_INTERRUPTED = SignalBitmask(0b00000010, "LIGHT_BARRIER_HEIGHT_NOT_INTERRUPTED");
SignalBitmask AsyncChannel::SENSOR_HEIGHT_MATCH = 				   SignalBitmask(0b00000100, "SENSOR_HEIGHT_MATCH");
SignalBitmask AsyncChannel::LIGHT_BARRIER_SWITCH_NOT_INTERRUPTED = SignalBitmask(0b00001000, "LIGHT_BARRIER_SWITCH_NOT_INTERRUPTED");
SignalBitmask AsyncChannel::SENSOR_METAL_MATCH = 				   SignalBitmask(0b00010000, "SENSOR_METAL_MATCH");
SignalBitmask AsyncChannel::LIGHT_BARRIER_SLIDE_NOT_INTERRUPTED =  SignalBitmask(0b00100000, "LIGHT_BARRIER_SLIDE_NOT_INTERRUPTED");
SignalBitmask AsyncChannel::SENSOR_SWITCH_IS_OPEN = 			   SignalBitmask(0b01000000, "SENSOR_SWITCH_IS_OPEN");
SignalBitmask AsyncChannel::LIGHT_BARRIER_OUTPUT_NOT_INTERRUPTED = SignalBitmask(0b10000000, "LIGHT_BARRIER_OUTPUT_NOT_INTERRUPTED");

AsyncChannel::AsyncChannel() {
	LOG_SCOPE
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
	LOG_SCOPE
	ConnectDetach(connectionId);
	ChannelDestroy(channelId);

	//LOG_HAL("Channel destroyed");
}

AsyncMsg AsyncChannel::getNextMessage(){
	LOG_SCOPE
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
	LOG_SCOPE
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
	LOG_SCOPE
	return connectionId;
}

AsyncChannel& AsyncChannel::getChannel(){
	LOG_SCOPE
	static AsyncChannel instance;
	return instance;
}

} /* io */
} /* hal */
