#pragma once

#include <utility>
#include <memory>

// pimpl wrapper based on code from http://herbsutter.com/gotw/_101/

namespace ml {

template<typename T>
class pimpl 
{
private:
	std::unique_ptr<T> m_impl;

public:
	pimpl();
    template<typename Arg1>
    pimpl(Arg1&& arg1);

    template<typename Arg1, typename Arg2>
    pimpl(Arg1&& arg1, Arg2&& arg2);

    template<typename Arg1, typename Arg2, typename Arg3>
    pimpl( Arg1&& arg1, Arg2&& arg2, Arg3&& arg3 );


	~pimpl();


	const T* operator->() const;
	T* operator->();
	const T& operator*() const;
	T& operator*();
};


template<typename T>
pimpl<T>::pimpl() : m_impl(new T) 
{
}

template<typename T>
    template<typename Arg1>
pimpl<T>::pimpl(Arg1&& arg1)
    : m_impl(new T(std::forward<Arg1>(arg1))) 
{
}

template<typename T>
template<typename Arg1, typename Arg2>
pimpl<T>::pimpl(Arg1&& arg1, Arg2&& arg2)
    : m_impl(new T(std::forward<Arg1>(arg1), std::forward<Arg2>(arg2))) 
{
}

template<typename T>
template<typename Arg1, typename Arg2, typename Arg3>
pimpl<T>::pimpl(Arg1&& arg1, Arg2&& arg2, Arg3&& arg3)
    : m_impl(new T(std::forward<Arg1>(arg1), 
                    std::forward<Arg2>(arg2), 
                    std::forward<Arg3>(arg3))) 
{
}


template<typename T>
pimpl<T>::~pimpl() 
{
}

template<typename T>
const T* pimpl<T>::operator->() const
{
	return m_impl.get(); 
}

template<typename T>
T* pimpl<T>::operator->()
{
	return m_impl.get(); 
}

template<typename T>
T& pimpl<T>::operator*() 
{
	return *m_impl.get(); 
}

template<typename T>
const T& pimpl<T>::operator*() const
{
	return *m_impl.get(); 
}

} // namespace ml