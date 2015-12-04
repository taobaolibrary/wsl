/* ************************************************************************
 *       Filename:  pthread_util.h
 *       Description: 封装一些pthread的类
 *       Version:  1.0
 *       Created:  2015年12月04日 17时49分29秒
 *       Revision:  NONE
 *       Compiler:  g++
 *       Author:  wochenglin@qq.com
 *       Company:  YY.COM
* ************************************************************************/
#ifndef _WSL_PTHREAD_UTIL_H_
#define _WSL_PTHREAD_UTIL_H_

#include<pthread.h>
#include <semaphore.h>
#include <errno.h>
#include "functor.h"
#include "thread_util.h"

#if !defined(linux) && (defined(__linux) || defined(__linux__))
#define  linux
#endif

namespace wsl
{
	class Mutex
	{
	private:
		pthread_mutex_t m_mutex;

		Mutex(Mutex&);
		Mutex& operator= (const Mutex&);
	public:
		Mutex(){
			::pthread_mutex_init(& m_mutex);
		}
		~Mutex(){
			::pthread_mutex_destory(&m_mutex);
		}
		bool Lock(){ return 0 == ::pthread_mutex_lock(&m_mutex);}
		bool Unlock(){ return 0 == ::pthread_mutex_unlock(&m_mutex);}
		bool TryLock(){return 0 ==::pthread_mutex_trylock(&m_mutex);}
#ifdef _POSIX_TIMEOUTS
#	if _POSIX_TIMEOUTS >= 0
		bool Lock(const struct timespec& abstime)	{ return 0 == ::pthread_mutex_timedlock(&m_sect, &abstime); }
#	endif
#endif

	};
	typedef wsl::Locker<Mutex> MutexLocker;


	class Condition
	{
		pthread_cond_t m_cond;
		Condition(Condition&);
		Condition& operator=(Condition&);
	public:
		Condition() {::pthread_cond_init(&m_cond,NULL);}
		~Condition(){::pthread_cond_destory(&m_cond);}

		bool Signal() {return 0 ==::pthread_cond_signal(&m_cond);}
		bool Broadcast() {return 0 ==::pthread_cond_broadcast(&m_cond);}
		bool Wait(Mutex& m){return 0 ==::pthread_cond_wait(&m_cond,&m.m_mutex);}
		bool Wait(Mutex& m,const struct timespec&  abstime)
		{
			int r;
			do{ 
				r = ::pthread_cond_timedwait(&m_sect, &m.m_sect, &abstime);
			}while(r != 0 && r != ETIMEDOUT && r != EINVAL);
			return r == 0;

		}
	};


}

#endif
