#pragma once

#include "../../interface/NativeTypes.hh"

class IntType : public INativeType
{
  public:
    IntType(bool isSigned, std::size_t size)
        : _isSigned(isSigned), _size(size) {}

    std::string getTypeName() const override
    {
        if (_isSigned) {
            switch (_size) {
            case 1:
                return "int8_t";
            case 2:
                return "int16_t";
            case 4:
                return "int32_t";
            case 8:
                return "int64_t";
            default:
                throw std::runtime_error(
                    "Unsupported size for signed int type");
            }
        }
        else {
            switch (_size) {
            case 1:
                return "uint8_t";
            case 2:
                return "uint16_t";
            case 4:
                return "uint32_t";
            case 8:
                return "uint64_t";
            default:
                throw std::runtime_error(
                    "Unsupported size for unsigned int type");
            }
        }
    }

    std::size_t getSize() const override { return _size; }

    bool isC() const override { return true; }

    bool isNumber() const override { return true; }

    bool isSigned() const override { return _isSigned; }

    bool isStd() const override { return true; }

  private:
    const bool _isSigned;
    const std::size_t _size;
};

class Int8Type : public IntType
{
  public:
    Int8Type() : IntType(true, 1) {}
};

class Int16Type : public IntType
{
  public:
    Int16Type() : IntType(true, 2) {}
};

class Int32Type : public IntType
{
  public:
    Int32Type() : IntType(true, 4) {}
};

class Int64Type : public IntType
{
  public:
    Int64Type() : IntType(true, 8) {}
};

class UInt8Type : public IntType
{
  public:
    UInt8Type() : IntType(false, 1) {}
};

class UInt16Type : public IntType
{
  public:
    UInt16Type() : IntType(false, 2) {}
};

class UInt32Type : public IntType
{
  public:
    UInt32Type() : IntType(false, 4) {}
};

class UInt64Type : public IntType
{
  public:
    UInt64Type() : IntType(false, 8) {}
};

class CharType : public Int8Type
{
  public:
    CharType() : Int8Type() {}

    std::string getTypeName() const override { return "char"; }

    bool isChar() const override { return true; }

    bool isStd() const override { return false; }
};
