#pragma once
#include <boost/function.hpp>
#include <boost/thread.hpp>


namespace zm
{


	inline void __inner_parallel_do(
		boost::function<void(int)> f
		, int size)
	{
		#pragma omp parallel for
		for (int i = 0; i < size; i++)
		{
			f(i);
		}
	}



	inline void parallel_do(
		boost::function<void(int)> f
		, int size)
	{
		__inner_parallel_do(f, size);
	}

	inline void parallel_do(
		boost::function<void(std::size_t)> f
		, std::size_t size)
	{
		boost::function<void(std::size_t)> f_sz = [&](std::size_t idx) {
			f(idx);
		};
		__inner_parallel_do(f_sz, (int)size);
	}

	inline void parallel_do(
		boost::function<void(int i0, int i1)> f
		, int i0_sz, int i1_sz)
	{
		boost::function<void(int)> f_sz = [&](int idx) {
			int i0 = idx / i1_sz;
			int i1 = idx - i0 * i1_sz;
			f(i0, i1);
		};
		__inner_parallel_do(f_sz, (int)(i0_sz * i1_sz) );
	}


	inline void parallel_do_fake(
		boost::function<void(std::size_t)> f
		, std::size_t size)
	{
		for (std::size_t i = 0; i < size; i++)
		{
			f(i);
		}
	}

}



#define _inner_concat_name(name, line) name ## line
#define boost_lock_grad_(mtx, line) 	boost::mutex::scoped_lock  _inner_concat_name(__boost_lock,line)(mtx)
#define boost_lock_grad(mtx) boost_lock_grad_(mtx, __LINE__)

#define boost_recur_lock_grad_(mtx, line) 	boost::recursive_mutex::scoped_lock  _inner_concat_name(__boost_lock,line)(mtx)
#define boost_recur_lock_grad(mtx) boost_recur_lock_grad_(mtx, __LINE__)

typedef boost::shared_mutex ZmMutexType;
typedef boost::unique_lock< ZmMutexType >  ZmWriteLockType;
typedef boost::shared_lock< ZmMutexType >  ZmReadLockType;