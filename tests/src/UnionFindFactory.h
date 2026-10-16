#include "UnionFind.h"
#include "MyImplUnionFind.h"
#include <memory>


template <typename T>
struct SUnionFindFactory;

template<>
struct SUnionFindFactory<CMyImplUnionFind>{
    static std::unique_ptr<CUnionFind> Create(){
        return std::make_unique<CMyImplUnionFind>();
    }
};
