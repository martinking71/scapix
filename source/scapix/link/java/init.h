/*
	scapix/link/java/init.h

	Copyright (c) 2019-2022 Boris Rasin (boris@scapix.com)
*/

#ifndef SCAPIX_LINK_JAVA_INIT_H
#define SCAPIX_LINK_JAVA_INIT_H

#include <scapix/link/java/env.h>
#include <scapix/link/java/detail/native_exception.h>
#include <scapix/link/java/native_method.h>

#ifdef SCAPIX_CACHE_CLASS_LOADER
#include <scapix/link/java/class_loader.h>
#endif

namespace scapix::link::java {

inline jint on_load(JavaVM *vm, void *reserved) noexcept
{
	detail::jvm_ptr = vm;
	get_env();

#ifdef SCAPIX_CACHE_CLASS_LOADER
	class_loader::init();
#endif

	native_methods
	<
		detail::native_exception::class_name,
		native_method<SCAPIX_META_STRING("finalize"), void(jlong), void(std::int64_t), &detail::native_exception::finalize>
	>
	::register_();

	return JNI_VERSION_1_6;
}

inline void on_unload(JavaVM *vm, void *reserved) noexcept
{
	detail::jvm_ptr = nullptr;
}

} // namespace scapix::link::java

#endif // SCAPIX_LINK_JAVA_INIT_H