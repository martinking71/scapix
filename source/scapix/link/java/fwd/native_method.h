/*
	scapix/link/java/fwd/native_method.h

	Copyright (c) 2019-2023 Boris Rasin (boris@scapix.com)
*/

#ifndef SCAPIX_LINK_JAVA_FWD_NATIVE_METHOD_H
#define SCAPIX_LINK_JAVA_FWD_NATIVE_METHOD_H

#include <type_traits>
#include <scapix/core/fixed_string.h>

namespace scapix::link::java {

template <fixed_string ClassName, typename ...Methods>
class native_methods;

template <fixed_string Name, typename JniType, typename Type, std::decay_t<Type> Method>
struct native_method;

} // namespace scapix::link::java

#endif // SCAPIX_LINK_JAVA_FWD_NATIVE_METHOD_H
