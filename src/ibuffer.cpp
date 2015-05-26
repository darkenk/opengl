#include "ibuffer.hpp"

#include "utils/logger.hpp"

IBuffer::~IBuffer()
{
}

void IBuffer::setAttributes(const AttributeVector&) const
{
    LOGV << "setAttributes from IBuffer";
}
