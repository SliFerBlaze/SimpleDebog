#pragma once

#include "../../interface/NativeTypes.hh"
#include <memory>
#include <string>

class PointerType : public INativeType
{
  public:
    PointerType(std::shared_ptr<INativeType> pointeeType, bool isArray = false)
        : _pointeeType(pointeeType), _isArray(isArray)
    {
    }

    std::string getTypeName() const override
    {
        return _pointeeType->getTypeName() + "*";
    }

    std::size_t getSize() const override
    {
        return sizeof(void *);
    }

    bool isC() const override { return true; }

    bool isPointer() const override { return true; }

    bool isFunction() const override { return _pointeeType->isFunction(); }

    bool isCpp() const override { return _pointeeType->isCpp(); }

    bool isStd() const override { return _pointeeType->isStd(); }

    bool isTemplate() const override { return _pointeeType->isTemplate(); }

    bool isArray() const override
    {
        return _pointeeType->isArray() || _isArray;
    }

    std::shared_ptr<INativeType> getPointeeType() const
    {
        return _pointeeType;
    }

  private:
    const std::shared_ptr<INativeType> _pointeeType;
    const bool _isArray;
};
