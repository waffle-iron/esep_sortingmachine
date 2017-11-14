/*
 * Parameter.h
 *
 *  Created on: Nov 9, 2017
 *      Author: stammtisch
 */

#ifndef PARAMETER_H_
#define PARAMETER_H_

#include "ParameterBase.h"
#include <iostream>
#include <cstdint>


using namespace std;

template <class T>
class Parameter : public ParameterBase {
public:
	explicit Parameter() :
	value(0)
	{
		parameterList.parameters.push_back(this);
	}

	explicit Parameter(T value, string name) :
	ParameterBase(name),
	value(value)
	{
	}

	virtual ~Parameter()
	{
	}

	operator T() const
	{
		return value;
	}

	const Parameter<T>& operator=(const Parameter<T>& other) {
		if(other == *this) {
			return *this;
		}
		ParameterBase::operator =(other);
		value = other.value;
		return *this;
	}

	void showValue()
	{
		cout<<name<<": "<<(int)value<<endl;
	}

	T value;
};

extern Parameter<uint8_t> cb_this;
extern Parameter<uint8_t> cb_last;
extern Parameter<uint8_t> cb_all;
extern Parameter<uint8_t> cb_available;

#endif /* PARAMETER_H_ */
