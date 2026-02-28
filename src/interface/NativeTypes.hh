#pragma once
#include <cstddef>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

class INativeType
{
  public:
    virtual ~INativeType() = default;

    // Returns the type name of the native type
    virtual std::string getTypeName() const = 0;

    // Returns the size of the native type in bytes according to sizeof operator.
    // Idk if it'll work for the size of types in the debugged process.
    virtual std::size_t getSize() const = 0;

    // Returns true if the type is a C language type
    virtual bool isC() const { return false; };

    // Returns true if the type is a number (integer or floating point)
    virtual bool isNumber() const { return false; };

    // Returns true if the type is signed (only valid for number types)
    virtual bool isSigned() const { return false; };

    // Returns true if the type is a character type
    virtual bool isChar() const { return false; };

    // Returns true if the type is an array type
    virtual bool isArray() const { return false; };

    // Returns true if the type is a struct type
    virtual bool isStruct() const { return false; };

    // Returns true if the type is a union type
    virtual bool isUnion() const { return false; };

    // Returns true if the type is a pointer type
    virtual bool isPointer() const { return false; };

    // Returns true if the type is a function type (only valid for pointer types)
    virtual bool isFunction() const { return false; };

    // Returns true if the type is a C++ language type
    virtual bool isCpp() const { return false; };

    // Returns true if the type is a type defined in the std namespace
    virtual bool isStd() const { return false; };

    // Returns true if the type is a template type
    virtual bool isTemplate() const { return false; };
};

class INativeTypeValue
{
  public:
    virtual ~INativeTypeValue() = default;

    // Returns a pointer to the native type of this value
    virtual const INativeType &getType() const = 0;

    // Returns the size of the value in bytes
    virtual std::size_t getSize() const
    {
        const INativeType &type = getType();
        if (!type.isC()) {
            throw std::runtime_error("Size retrieval only implemented for C types on the interface level");
        }
        if (type.isArray()) {
            throw std::runtime_error("Size of arrays not implemented on the interface level");
        }
        if (type.isStruct()) {
            throw std::runtime_error("Size of structs not implemented on the interface level");
        }
        if (type.isUnion()) {
            throw std::runtime_error("Size of unions not implemented on the interface level");
        }
        return type.getSize();
    };

    // Returns the value as a string
    virtual std::string toString() const = 0;
};

class NativeTypeRegistry
{
  public:
    static void registerType(
        const std::string &name,
        std::shared_ptr<INativeType> type,
        bool overwrite = false)
    {
        if (!overwrite && hasType(name)) {
            throw std::runtime_error("Native type already registered: " + name);
        }
        nativeTypeRegistry[name] = type;
    }

    static void unregisterType(const std::string &name)
    {
        nativeTypeRegistry.erase(name);
    }

    static bool hasType(const std::string &name)
    {
        return nativeTypeRegistry.find(name) != nativeTypeRegistry.end();
    }

    static std::shared_ptr<INativeType> getType(const std::string &name)
    {
        auto it = nativeTypeRegistry.find(name);
        if (it != nativeTypeRegistry.end()) {
            return it->second;
        }
        throw std::runtime_error("Native type not found: " + name);
    }

  private:
    static std::map<std::string, std::shared_ptr<INativeType>> nativeTypeRegistry;
};
