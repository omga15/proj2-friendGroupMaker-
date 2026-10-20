#ifndef MY_IMPL_UNION_FIND_H
#define MY_IMPL_UNION_FIND_H

#include "UnionFind.h"
#include <memory>

class CMyImplUnionFind: public CUnionFind{
    private:
        struct SImplementation;
        std::unique_ptr<SImplementation> DImplementation;
    public:
        CMyImplUnionFind();
        ~CMyImplUnionFind();
        std::size_t Size() const override;
        std::size_t GroupCount() const override;
        TElementID AddElement() override;
        bool Union(TElementID a, TElementID b) override;
        TGroupID Find(TElementID a) const override;
        bool Connected(TElementID a, TElementID b) override;
};

#endif