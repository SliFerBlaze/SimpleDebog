#include "./IntType.hh"
#include "../../interface/NativeTypes.hh"

void registerNativeTypes()
{
    // Register standard integer types
    NativeTypeRegistry::registerType("int8_t", std::make_shared<Int8Type>());
    NativeTypeRegistry::registerType("int16_t", std::make_shared<Int16Type>());
    NativeTypeRegistry::registerType("int32_t", std::make_shared<Int32Type>());
    NativeTypeRegistry::registerType("int64_t", std::make_shared<Int64Type>());
    NativeTypeRegistry::registerType("uint8_t", std::make_shared<UInt8Type>());
    NativeTypeRegistry::registerType("uint16_t", std::make_shared<UInt16Type>());
    NativeTypeRegistry::registerType("uint32_t", std::make_shared<UInt32Type>());
    NativeTypeRegistry::registerType("uint64_t", std::make_shared<UInt64Type>());
    NativeTypeRegistry::registerType("char", std::make_shared<CharType>());
    NativeTypeRegistry::registerType("signed char", std::make_shared<CharType>());
    NativeTypeRegistry::registerType("unsigned char", std::make_shared<UInt8Type>());
    NativeTypeRegistry::registerType("short", std::make_shared<Int16Type>());
    NativeTypeRegistry::registerType("unsigned short", std::make_shared<UInt16Type>());
    NativeTypeRegistry::registerType("int", std::make_shared<Int32Type>());
    NativeTypeRegistry::registerType("unsigned int", std::make_shared<UInt32Type>());
    NativeTypeRegistry::registerType("long", std::make_shared<Int64Type>());
    NativeTypeRegistry::registerType("unsigned long", std::make_shared<UInt64Type>());
    NativeTypeRegistry::registerType("long long", std::make_shared<Int64Type>());
    NativeTypeRegistry::registerType("unsigned long long", std::make_shared<UInt64Type>());
}
