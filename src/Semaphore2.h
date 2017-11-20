/*
 * Semaphore.h
 *
 *  Created on: 13.11.2017
 *      Author: aca311
 */

#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#pragma once
#include <cstddef>
#include <mutex>
#include <condition_variable>

class Semaphore2 {
public:
	Semaphore2(const size_t count = 0) :
    count_(count),
    condition_(),
    mtx_()
    {

    }

	~Semaphore2(){
		std::cout <<  "enter semaphore destruct" << std::endl;
	}

	Semaphore2(const Semaphore2&) = delete;
	Semaphore2& operator=(const Semaphore2&) = delete;
	Semaphore2(Semaphore2&&) = delete;
	Semaphore2& operator=(Semaphore2&&) = delete;

    inline void post(void) {
        std::lock_guard<std::mutex> lock(mtx_);
        count_++;
        condition_.notify_one();
    }

    inline void wait(void) {
        std::unique_lock<std::mutex> lock(mtx_);
        condition_.wait(lock, [&]{return count_>0;});
        count_--;
    }

    inline bool try_wait(void) {
        std::unique_lock<std::mutex> lock(mtx_);
        if(count_ > 0) {
            count_--;
            return true;
        }
        return false;
	}

	inline size_t get_value() const {return count_;}
	void destroy() {

		std::cout << "notify" << std::endl;
		condition_.notify_all();
		std::cout << "after notify" << std::endl;

	}

private:
    size_t count_;
    std::condition_variable condition_;
    std::mutex mtx_;
};

#endif /* SEMAPHORE_H_ */

