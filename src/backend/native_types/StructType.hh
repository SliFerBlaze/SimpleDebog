#pragma once

#include "../../interface/NativeTypes.hh"
#include <memory>
#include <string>
#include <vector>

class StructType : public INativeType
{
  public:
    struct Member {
        std::string name;
        std::shared_ptr<INativeType> type;
    };

    StructType(const std::string &name, const std::vector<Member> &members)
        : _name(name), _members(members)
    {
        _size = calculateSize();
    }

    std::string getTypeName() const override { return _name; }

    std::size_t getSize() const override { return _size; }

    bool isC() const override { return true; }

    bool isStruct() const override { return true; }

    const std::vector<Member> &getMembers() const { return _members; }

  private:
    std::string _name;
    std::vector<Member> _members;
    std::size_t _size;

    std::size_t calculateSize() const
    {
        std::size_t totalSize = 0;
        for (const auto &member : _members) {
            totalSize += member.type->getSize();
        }
        return totalSize;
    }
};
