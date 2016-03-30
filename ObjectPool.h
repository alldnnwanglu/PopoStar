//
//  ObjectPool.h
//  HelloCpp
//
//  Created by shaoleibo on 15-2-2.
//  Copyright (c) 2015年 Bullets in a Burning Box, Inc. All rights reserved.
//

#ifndef HelloCpp_ObjectPool_h
#define HelloCpp_ObjectPool_h
#include <queue>
#include <vector>
#include <stdexcept>
#include <memory>
using std::queue;
using std::vector;

template <typename T>
class ObjectPool
{
public:
    ObjectPool( int chunkSize = 100 );
    ~ObjectPool();
    T& acquireObject();
    void releaseObject( T& obj );
protected:
    int m_chunkSize;
    queue<T*> m_freeList;
    vector<T*> m_allObjects;
    void allocateChunk();
    static void arrayDeleteObject(T* obj);
private:
    ObjectPool(const ObjectPool<T>& src);
    ObjectPool<T>& operator=(const ObjectPool<T>& rhs);
};

template <typename T>
ObjectPool<T>::ObjectPool( int chunkSize )
{
	m_chunkSize = chunkSize;
	allocateChunk();
}

template <typename T>
void ObjectPool<T>::allocateChunk()
{
	T* newObjects = new T[m_chunkSize];
    m_allObjects.push_back( newObjects );
	for ( int i = 0; i < m_chunkSize; i++ )
	{
		m_freeList.push(&newObjects[i]);
	}
}

template <typename T>
T& ObjectPool<T>::acquireObject()
{
	if ( m_freeList.empty() ) {
		allocateChunk();
	}
	T* obj = m_freeList.front();
	m_freeList.pop();
	return ( *obj );
}

template <typename T>
void ObjectPool<T>::arrayDeleteObject(T* obj)
{
    delete [] obj;
}

template <typename T>
ObjectPool<T>::~ObjectPool()
{
	// free each of the allocation chunks
	for_each( m_allObjects.begin(), m_allObjects.end(), arrayDeleteObject);
}

template <typename T>
void ObjectPool<T>::releaseObject(T& obj)
{
	m_freeList.push( &obj );
}

#endif