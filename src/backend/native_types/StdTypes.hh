#pragma once

#include "../../interface/NativeTypes.hh"
#include "./PointerType.hh"
#include <memory>
#include <regex>
#include <set>
#include <string>
#include <vector>

class StdType : public INativeType
{
  public:
    StdType(const std::string &typeName,
            const std::vector<std::shared_ptr<INativeType>> &templateParams = {})
        : _typeName(typeName),
          _templateParams(templateParams),
          _isArray(stdTestArray(typeName)),
          _isFunction(stdTestFunction(typeName)),
          _isTemplate(!_templateParams.empty()),
          _isPointer(stdTestPointer(typeName)),
          _size(calculateSize())
    {
    }

    std::string getTypeName() const override { return _typeName; }

    std::size_t getSize() const override
    {
        return _size;
    }

    bool isCpp() const override { return true; }

    bool isStd() const override { return true; }

    bool isTemplate() const override { return _isTemplate; }

    bool isArray() const override { return _isArray; }

    bool isFunction() const override { return _isFunction; }

    bool isPointer() const override { return _isPointer; }

    const std::vector<std::shared_ptr<INativeType>> &getTemplateParams() const
    {
        return _templateParams;
    }

  private:
    const std::string _typeName;
    const std::vector<std::shared_ptr<INativeType>> _templateParams;
    const std::size_t _size;
    const bool _isArray;
    const bool _isFunction;
    const bool _isTemplate;
    const bool _isPointer;

    static bool stdTestArray(const std::string &typeName)
    {
        const std::set<std::string> allArrayTypes = {
            "std::array",
            "std::vector",
            "std::deque",
            "std::list",
            "std::forward_list",
            "std::set",
            "std::unordered_set",
            "std::map",
            "std::unordered_map",
            "std::multiset",
            "std::unordered_multiset",
            "std::multimap",
            "std::unordered_multimap",
            "std::stack",
            "std::queue",
            "std::priority_queue",
            "std::span",
            "std::valarray",
            "std::basic_string",
            "std::string",
            "std::wstring",
            "std::u16string",
            "std::u32string",
            "std::bitset"};
        return allArrayTypes.find(typeName) != allArrayTypes.end();
    }

    static bool stdTestFunction(const std::string &typeName)
    {
        const std::set<std::string> allFunctionTypes = {
            "std::function",
            "std::bind",
            "std::mem_fn",
            "std::invoke",
            "std::apply",
            "std::thread",
            "std::async",
            "std::packaged_task",
            "std::jthread",
            "std::stop_token",
            "std::stop_source",
            "std::stop_callback"};
        return allFunctionTypes.find(typeName) != allFunctionTypes.end();
    }

    static bool stdTestPointer(const std::string &typeName)
    {
        const std::set<std::string> allPointerTypes = {
            "std::shared_ptr",
            "std::unique_ptr",
            "std::weak_ptr",
            "std::auto_ptr",
            "std::reference_wrapper",
            "std::observer_ptr",
            "std::pointer_traits",
            "std::pointer_safety",
            "std::pointer_arithmetic"};
        return allPointerTypes.find(typeName) != allPointerTypes.end();
    }

    // Here getDebugSymbols is a placeholder for the actual implementation of
    // retrieving type information from debug symbols,
    // which is not implemented yet.
    std::size_t calculateSize()
    {
        if (_isPointer || _isArray) {
            throw std::runtime_error(
                "Size of pointer and array types not implemented yet");
            // return getDebugSymbols(_typeName).size;
        }
        if (_isTemplate && !_templateParams.empty()) {
            std::size_t totalSize = 0;
            for (const auto &param : _templateParams) {
                totalSize += param->getSize();
            }
            return totalSize;
        }
        throw std::runtime_error(
            "Size of std types not implemented yet");
        // return getDebugSymbols(_typeName).size;
    }
};

class StdTypeParser
{
  public:
    static std::shared_ptr<INativeType> parseStdType(
        const std::string &typeStr)
    {
        std::string trimmed = trim(typeStr);

        if (trimmed.empty()) {
            throw std::runtime_error("Cannot parse empty type string");
        }

        if (NativeTypeRegistry::hasType(trimmed)) {
            return NativeTypeRegistry::getType(trimmed);
        }

        if (trimmed[0] == '*') {
            return std::make_shared<PointerType>(
                parseStdType(trimmed.substr(1)));
        }

        if (trimmed.back() == '*') {
            return std::make_shared<PointerType>(
                parseStdType(trimmed.substr(0, trimmed.length() - 1)));
        }

        size_t openBracket = trimmed.find('<');
        if (openBracket == std::string::npos) {
            return std::make_shared<StdType>(trimmed);
        }

        std::string baseName = trimmed.substr(0, openBracket);
        std::vector<std::shared_ptr<INativeType>> params =
            extractTemplateParams(trimmed, openBracket);

        return std::make_shared<StdType>(baseName, params);
    }

  private:
    static std::string trim(const std::string &str)
    {
        size_t start = str.find_first_not_of(" \t\n\r");
        size_t end = str.find_last_not_of(" \t\n\r");
        return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
    }

    static std::vector<std::shared_ptr<INativeType>>
    extractTemplateParams(const std::string &typeStr, size_t openPos)
    {
        std::vector<std::shared_ptr<INativeType>> params;
        int bracketCount = 0;
        std::string currentParam;

        for (size_t i = openPos + 1; i < typeStr.length(); ++i) {
            char c = typeStr[i];

            if (c == '<') {
                bracketCount++;
                currentParam += c;
            }
            else if (c == '>') {
                if (bracketCount == 0) {
                    if (!currentParam.empty()) {
                        params.push_back(parseStdType(currentParam));
                    }
                    break;
                }
                bracketCount--;
                currentParam += c;
            }
            else if (c == ',' && bracketCount == 0) {
                if (!currentParam.empty()) {
                    params.push_back(parseStdType(currentParam));
                    currentParam.clear();
                }
            }
            else {
                currentParam += c;
            }
        }

        return params;
    }
};
