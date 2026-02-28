#pragma once

#include "../../interface/NativeTypes.hh"
#include <memory>
#include <string>

class ArrayType : public INativeType
{
  public:
    ArrayType(
        std::shared_ptr<INativeType> elementType,
        std::size_t elementCount)
        : _elementType(elementType),
          _elementCount(elementCount),
          _size(_elementType->getSize() * _elementCount)
    {
    }

    std::string getTypeName() const override
    {
        return _elementType->getTypeName() + "[" +
               std::to_string(_elementCount) + "]";
    }

    std::size_t getSize() const override { return _size; }

    bool isC() const override { return _elementType->isC(); }

    bool isArray() const override { return true; }

    std::shared_ptr<INativeType> getElementType() const
    {
        return _elementType;
    }

    std::size_t getElementCount() const { return _elementCount; }

  private:
    const std::shared_ptr<INativeType> _elementType;
    const std::size_t _elementCount;
    const std::size_t _size;
};
