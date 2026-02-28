#pragma once

#include "../../interface/NativeTypes.hh"
#include <memory>
#include <string>
#include <vector>

class UnionType : public INativeType
{
  public:
    struct Member {
        std::string name;
        std::shared_ptr<INativeType> type;
    };

    UnionType(const std::string &name, const std::vector<Member> &members)
        : _name(name), _members(members), _size(calculateSize())
    {
    }

    std::string getTypeName() const override { return _name; }

    std::size_t getSize() const override { return _size; }

    bool isC() const override { return true; }

    bool isUnion() const override { return true; }

    const std::vector<Member> &getMembers() const { return _members; }

  private:
    // Original name of the union, not necessarily unique
    const std::string _name;
    const std::vector<Member> _members;
    const std::size_t _size;

    std::size_t calculateSize() const
    {
        std::size_t totalSize = 0;
        for (const auto &member : _members) {
            if (member.type->getSize() > totalSize) {
                totalSize = member.type->getSize();
            }
        }
        return totalSize;
    }
};
