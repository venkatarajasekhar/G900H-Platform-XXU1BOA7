
/*
 * Copyright 2011 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#ifndef SkPathHeap_DEFINED
#define SkPathHeap_DEFINED

#include "SkRefCnt.h"
#include "SkChunkAlloc.h"
#include "SkTDArray.h"

class SkPath;
class SkReadBuffer;
class SkWriteBuffer;

class SkPathHeap : public SkRefCnt {
public:
    SK_DECLARE_INST_COUNT(SkPathHeap)

    SkPathHeap();
    SkPathHeap(SkReadBuffer&);
    virtual ~SkPathHeap();

    /** Copy the path into the heap, and return the new total number of paths.
        Thus, the returned value will be index+1, where index is the index of
        this newly added (copied) path.
     */
    int append(const SkPath&);

    // called during picture-playback
    int count() const { return fPaths.count(); }
    const SkPath& operator[](int index) const {
        return *fPaths[index];
    }

    void flatten(SkWriteBuffer&) const;

private:
    // we store the paths in the heap (placement new)
    SkChunkAlloc        fHeap;
    // we just store ptrs into fHeap here
    SkTDArray<SkPath*>  fPaths;

    typedef SkRefCnt INHERITED;
};

#endif