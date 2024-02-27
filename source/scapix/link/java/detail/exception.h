/*
	scapix/link/java/detail/exception.h

	Copyright (c) 2019-2023 Boris Rasin (boris@scapix.com)
*/

#ifndef SCAPIX_LINK_JAVA_DETAIL_EXCEPTION_H
#define SCAPIX_LINK_JAVA_DETAIL_EXCEPTION_H

#include <scapix/link/java/type_traits.h>
#include <scapix/link/java/ref.h>

namespace scapix::link::java::detail {

[[noreturn]] void throw_exception(jthrowable e = env()->ExceptionOccurred());
[[noreturn]] void throw_exception_nested(jthrowable e = env()->ExceptionOccurred());

inline void check_exception()
{
	jthrowable e = env()->ExceptionOccurred();

	if (e != 0) [[unlikely]]
		throw_exception(e);
}

inline void check_exception_nested()
{
	jthrowable e = env()->ExceptionOccurred();

	if (e != 0) [[unlikely]]
		throw_exception_nested(e);
}

inline jfieldID check_result(jfieldID id)
{
	if (!id) [[unlikely]]
		throw_exception();

	return id;
}

inline jmethodID check_result(jmethodID id)
{
	if (!id) [[unlikely]]
		throw_exception();

	return id;
}

// RegisterNatives()

inline jint check_result(jint i)
{
	if (i) [[unlikely]]
		throw_exception();

	return i;
}

// Get<PrimitiveType>ArrayElements(), GetPrimitiveArrayCritical()

template <typename T, typename = std::enable_if_t<is_primitive_v<T>>>
inline T* check_result(T* p)
{
	if (!p) [[unlikely]]
		throw_exception();

	return p;
}

template <typename T>
inline local_ref<T> check_result(jobject obj)
{
	if (!obj) [[unlikely]]
		throw_exception();

	return local_ref<T>(obj);
}

template <typename T>
inline local_ref<T> check_result_nested(jobject obj)
{
	if (!obj) [[unlikely]]
		throw_exception_nested();

	return local_ref<T>(obj);
}

struct check_exception_on_destroy
{
	check_exception_on_destroy() = default;
	~check_exception_on_destroy() noexcept(false) { check_exception(); }

	check_exception_on_destroy(const check_exception_on_destroy&) = delete;
	check_exception_on_destroy(check_exception_on_destroy&&) = delete;
	check_exception_on_destroy& operator = (const check_exception_on_destroy&) = delete;
	check_exception_on_destroy& operator = (check_exception_on_destroy&&) = delete;
};

struct check_exception_nested_on_destroy
{
	check_exception_nested_on_destroy() = default;
	~check_exception_nested_on_destroy() noexcept(false) { check_exception_nested(); }

	check_exception_nested_on_destroy(const check_exception_nested_on_destroy&) = delete;
	check_exception_nested_on_destroy(check_exception_nested_on_destroy&&) = delete;
	check_exception_nested_on_destroy& operator = (const check_exception_nested_on_destroy&) = delete;
	check_exception_nested_on_destroy& operator = (check_exception_nested_on_destroy&&) = delete;
};

} // namespace scapix::link::java::detail

#endif // SCAPIX_LINK_JAVA_DETAIL_EXCEPTION_H
