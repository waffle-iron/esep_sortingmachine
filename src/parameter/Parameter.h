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
	explicit Parameter()
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
		ParameterBase::operator =(other);
		value = other.value;
		return *this;
	}

	void showValue()
	{
		cout<<name<<": "<<value<<endl;
	}

	T value;
};

extern Parameter<uint8_t> cb_this;
extern Parameter<uint8_t> cb_last;

#endif /* PARAMETER_H_ */
