// ======================================================================== //
// Copyright 2009-2013 Intel Corporation                                    //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#ifndef __EMBREE_BVH4_INTERSECTOR4_HYBRID_H__
#define __EMBREE_BVH4_INTERSECTOR4_HYBRID_H__

#include "bvh4.h"
#include "../include/intersector4.h"

namespace embree
{
  /*! BVH4 Traverser. Packet traversal implementation for a Quad BVH. */
  template<typename TriangleIntersector4>
    class BVH4Intersector4Hybrid : public Intersector4
  {
    /* shortcuts for frequently used types */
    typedef typename TriangleIntersector4::Triangle Triangle;
    typedef typename TriangleIntersector4::TriangleIntersector1 TriangleIntersector1;
    typedef typename BVH4::NodeRef NodeRef;
    typedef typename BVH4::Node Node;
   
  public:

    BVH4Intersector4Hybrid (const BVH4* bvh) 
      : Intersector4((intersectFunc)intersect,(occludedFunc)occluded), bvh(bvh) {}

    static Intersector4* create(const Accel* bvh) { 
      return new BVH4Intersector4Hybrid((const BVH4*)bvh); 
    }

    static   void intersect(const BVH4Intersector4Hybrid* This, Ray4& ray, const __m128 valid);
    static __m128 occluded (const BVH4Intersector4Hybrid* This, Ray4& ray, const __m128 valid);

  private:
    const BVH4* bvh;
  };
}

#endif
