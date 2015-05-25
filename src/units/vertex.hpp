/**
 * Copyright (C) 2015, Dariusz Kluska <darkenk@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the {organization} nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef VERTEX_HPP
#define VERTEX_HPP

#include<type_traits>
#include "utils/exceptions.hpp"
#include "units.hpp"
#include <GL/gl.h>

#pragma GCC diagnostic ignored "-Winvalid-offsetof"
struct NodeNull1 {};
struct NodeNull2 {};
struct NodeNull3 {};
struct NodeNull4 {};
struct NodeNull5 {};
struct NodeNull6 {};
struct NodeNull7 {};
struct NodeNull8 {};
struct NodeNull9 {};

template<class T>
struct NodeV0 {
    T v0;
};

template<class T>
struct NodeV1 {
    T v1;
};

template<class T>
struct NodeV2 {
    T v2;
};

template<class T>
struct NodeV3 {
    T v3;
};

template<class T>
struct NodeV4 {
    T v4;
};

template<class T>
struct NodeV5 {
    T v5;
};

template<class T>
struct NodeV6 {
    T v6;
};

template<class T>
struct NodeV7 {
    T v7;
};

template<class T>
struct NodeV8 {
    T v8;
};

template<class T>
struct NodeV9 {
    T v9;
};

template<class V0, class V1 = NodeNull1, class V2 = NodeNull2, class V3 = NodeNull3,
         class V4 = NodeNull4, class V5 = NodeNull5, class V6 = NodeNull6,
         class V7 = NodeNull7, class V8 = NodeNull8, class V9 = NodeNull9>
class Vertex : public NodeV0<V0>,
    public std::conditional<std::is_same<V1, NodeNull1>::value, NodeNull1, NodeV1<V1>>::type,
    public std::conditional<std::is_same<V2, NodeNull2>::value, NodeNull2, NodeV2<V2>>::type,
    public std::conditional<std::is_same<V3, NodeNull3>::value, NodeNull3, NodeV3<V3>>::type,
    public std::conditional<std::is_same<V4, NodeNull4>::value, NodeNull4, NodeV4<V4>>::type,
    public std::conditional<std::is_same<V5, NodeNull5>::value, NodeNull5, NodeV5<V5>>::type,
    public std::conditional<std::is_same<V6, NodeNull6>::value, NodeNull6, NodeV6<V6>>::type,
    public std::conditional<std::is_same<V7, NodeNull7>::value, NodeNull7, NodeV7<V7>>::type,
    public std::conditional<std::is_same<V8, NodeNull8>::value, NodeNull8, NodeV8<V8>>::type,
    public std::conditional<std::is_same<V9, NodeNull9>::value, NodeNull9, NodeV9<V9>>::type
{
public:
    Vertex(V0 _v0 = V0{}, V1 _v1 = V1{}, V2 _v2 = V2{}, V3 _v3 = V3{}, V4 _v4 = V4{},
           V5 _v5 = V5{}, V6 _v6 = V6{}, V7 _v7 = V7{}, V8 _v8 = V8{}, V9 _v9 = V9{})
        : NodeV0<V0>{_v0} {
        init<1, V1>(_v1);
        init<2, V2>(_v2);
        init<3, V3>(_v3);
        init<4, V4>(_v4);
        init<5, V5>(_v5);
        init<6, V6>(_v6);
        init<7, V7>(_v7);
        init<8, V8>(_v8);
        init<9, V9>(_v9);
    }

    static GLenum getType(uint32_t i) {
        switch(i) {
        case 0: return getType_internal<V0>();
        case 1: return getType_internal<V1>();
        case 2: return getType_internal<V2>();
        case 3: return getType_internal<V3>();
        case 4: return getType_internal<V4>();
        case 5: return getType_internal<V5>();
        case 6: return getType_internal<V6>();
        case 7: return getType_internal<V7>();
        case 8: return getType_internal<V8>();
        case 9: return getType_internal<V9>();
        default:
            throw Exception("Incorrect offset of type");
        }
    }

    static GLint getSize(uint32_t i) {
        switch(i) {
        case 0: return getSize_internal<V0>();
        case 1: return getSize_internal<V1>();
        case 2: return getSize_internal<V2>();
        case 3: return getSize_internal<V3>();
        case 4: return getSize_internal<V4>();
        case 5: return getSize_internal<V5>();
        case 6: return getSize_internal<V6>();
        case 7: return getSize_internal<V7>();
        case 8: return getSize_internal<V8>();
        case 9: return getSize_internal<V9>();
        default:
            throw Exception("Incorrect offset of size");
        }
    }

    static uint32_t getOffset(uint32_t i) {
        switch(i) {
        case 0: return 0;
        case 1: return getOffset_internal<V1, 1>();
        case 2: return getOffset_internal<V2, 2>();
        case 3: return getOffset_internal<V3, 3>();
        case 4: return getOffset_internal<V4, 4>();
        case 5: return getOffset_internal<V5, 5>();
        case 6: return getOffset_internal<V6, 6>();
        case 7: return getOffset_internal<V7, 7>();
        case 8: return getOffset_internal<V8, 8>();
        case 9: return getOffset_internal<V9, 9>();
        default:
            throw Exception("Incorrect offset");
        }
        return 0;
    }
    friend std::ostream& operator<<(std::ostream& o, const Vertex& v) {
        return o << "Vertex " << v.v0;
    }
private:
    template<class T, uint32_t o, typename std::enable_if<std::is_empty<T>::value>::type* = nullptr>
    static uint32_t getOffset_internal() {
        throw Exception("Incorrect offset");
    }
    template<class T, uint32_t o, typename std::enable_if<not std::is_empty<T>::value &&
                                                          o == 1>::type* = nullptr>
    static uint32_t getOffset_internal() {
        return offsetof(Vertex, v1);
    }
    template<class T, uint32_t o, typename std::enable_if<not std::is_empty<T>::value &&
                                                          o == 2>::type* = nullptr>
    static uint32_t getOffset_internal() {
        return offsetof(Vertex, v2);
    }
    template<class T, uint32_t o, typename std::enable_if<not std::is_empty<T>::value &&
                                                          o == 3>::type* = nullptr>
    static uint32_t getOffset_internal() {
        return offsetof(Vertex, v3);
    }
    template<class T, uint32_t o, typename std::enable_if<not std::is_empty<T>::value &&
                                                          o == 4>::type* = nullptr>
    static uint32_t getOffset_internal() {
        return offsetof(Vertex, v4);
    }
    template<class T, uint32_t o, typename std::enable_if<not std::is_empty<T>::value &&
                                                          o == 5>::type* = nullptr>
    static uint32_t getOffset_internal() {
        return offsetof(Vertex, v5);
    }
    template<class T, uint32_t o, typename std::enable_if<not std::is_empty<T>::value &&
                                                          o == 6>::type* = nullptr>
    static uint32_t getOffset_internal() {
        return offsetof(Vertex, v6);
    }
    template<class T, uint32_t o, typename std::enable_if<not std::is_empty<T>::value &&
                                                          o == 7>::type* = nullptr>
    static uint32_t getOffset_internal() {
        return offsetof(Vertex, v7);
    }
    template<class T, uint32_t o, typename std::enable_if<not std::is_empty<T>::value &&
                                                          o == 8>::type* = nullptr>
    static uint32_t getOffset_internal() {
        return offsetof(Vertex, v8);
    }
    template<class T, uint32_t o, typename std::enable_if<not std::is_empty<T>::value &&
                                                          o == 9>::type* = nullptr>
    static uint32_t getOffset_internal() {
        return offsetof(Vertex, v9);
    }

    template<uint32_t o, class T,
             typename std::enable_if<std::is_empty<T>::value>::type* = nullptr>
    void init(T) {}

    template<uint32_t o, class T, typename std::enable_if<not std::is_empty<T>::value &&
                                                          o == 1>::type* = nullptr>
    void init(T _v1) {
        NodeV1<T>::v1 = _v1;
    }
    template<uint32_t o, class T, typename std::enable_if<not std::is_empty<T>::value &&
                                                          o == 2>::type* = nullptr>
    void init(T _v2) {
        NodeV2<T>::v2 = _v2;
    }
    template<uint32_t o, class T, typename std::enable_if<not std::is_empty<T>::value &&
                                                          o == 3>::type* = nullptr>
    void init(T _v3) {
        NodeV3<T>::v3 = _v3;
    }
    template<uint32_t o, class T, typename std::enable_if<not std::is_empty<T>::value &&
                                                          o == 4>::type* = nullptr>
    void init(T _v4) {
        NodeV4<T>::v4 = _v4;
    }
    template<uint32_t o, class T, typename std::enable_if<not std::is_empty<T>::value &&
                                                          o == 5>::type* = nullptr>
    void init(T _v5) {
        NodeV5<T>::v5 = _v5;
    }
    template<uint32_t o, class T, typename std::enable_if<not std::is_empty<T>::value &&
                                                          o == 6>::type* = nullptr>
    void init(T _v6) {
        NodeV6<T>::v6 = _v6;
    }
    template<uint32_t o, class T, typename std::enable_if<not std::is_empty<T>::value &&
                                                          o == 7>::type* = nullptr>
    void init(T _v7) {
        NodeV7<T>::v7 = _v7;
    }
    template<uint32_t o, class T, typename std::enable_if<not std::is_empty<T>::value &&
                                                          o == 8>::type* = nullptr>
    void init(T _v8) {
        NodeV8<T>::v8 = _v8;
    }
    template<uint32_t o, class T, typename std::enable_if<not std::is_empty<T>::value &&
                                                          o == 9>::type* = nullptr>
    void init(T _v9) {
        NodeV9<T>::v9 = _v9;
    }

    template<class T, typename std::enable_if<std::is_empty<T>::value>::type* = nullptr>
    static GLenum getType_internal() {
        throw Exception("GetType of incorrect offset");
    }
    template<class T, typename std::enable_if<not std::is_empty<T>::value>::type* = nullptr>
    static GLenum getType_internal() {
        return T::Type;
    }

    template<class T, typename std::enable_if<std::is_empty<T>::value>::type* = nullptr>
    static GLint getSize_internal() {
        throw Exception("GetSize of incorrect offset");
    }
    template<class T, typename std::enable_if<not std::is_empty<T>::value>::type* = nullptr>
    static GLint getSize_internal() {
        return T::Size;
    }
};

#include <vector>
#include <memory>

using Vertex3 = Vertex<Position, Color, Vector>;
typedef std::vector<Vertex3> VertexVector;
typedef std::shared_ptr<VertexVector> VertexVectorPtr;

typedef unsigned int Index;
typedef std::vector<Index> IndexVector;
typedef std::shared_ptr<IndexVector> IndexVectorPtr;

#endif // VERTEX_HPP

