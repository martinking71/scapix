/*
	scapix/link/java/byte_buffer.h

	Copyright (c) 2019-2022 Boris Rasin (boris@scapix.com)
*/

#ifndef SCAPIX_LINK_JAVA_BYTE_BUFFER_H
#define SCAPIX_LINK_JAVA_BYTE_BUFFER_H

#include <scapix/link/java/ref.h>
#include <scapix/link/java/object.h>

namespace scapix::link::java {

template <typename ClassName = SCAPIX_META_STRING("java/nio/ByteBuffer")>
class byte_buffer : public object<ClassName>
{
public:

	static local_ref<byte_buffer> new_direct(void* address, jlong capacity)
	{
		return local_ref<byte_buffer>(detail::env()->NewDirectByteBuffer(address, capacity));
	}

	void* direct_address() const
	{
		return detail::env()->GetDirectBufferAddress(this->handle());
	}

	jlong direct_capacity() const
	{
		return detail::env()->GetDirectBufferCapacity(this->handle());
	}

protected:

	using base = object<ClassName>;
	byte_buffer(typename base::handle_type h) : base(h) {}

};

// to do: fix dependence on handle template parameter (add third bool template parameter?)

//template <>
//class object<SCAPIX_META_STRING("java/nio/ByteBuffer")> : public byte_buffer<>
//{
//    using byte_buffer<>::byte_buffer;
//};

} // namespace scapix::link::java

#endif // SCAPIX_LINK_JAVA_BYTE_BUFFER_H
