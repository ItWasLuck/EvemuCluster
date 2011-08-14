/*
 * Ascent MMORPG Server
 * Copyright (C) 2005-2008 Ascent Team <http://www.ascentemu.com/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


#include "AscentPCH.h"
#include "BufferPool.h"

#ifdef ENABLE_BUFFER_POOLS

size_t BufferPool::BufferBucket::buffer_sizes[BUFFER_BUCKET_COUNT] = {
	20,			// 20 bytes
	50,			// 50 bytes
	100,		// 100 bytes
	200,		// 200 bytes
	500,		// 500 bytes
	1024,		// 1 kbyte
	5120,		// 5 kbyte
	10240,		// 10 kbyte (shouldn't be used much)
};



static int8 BufferPool::GetBufferPool(size_t sz)
{
	int8 x;
	for( x = 0; x < BUFFER_BUCKET_COUNT; ++x )
	{
		if( BufferBucket::buffer_sizes[x] >= sz )
			return x;
	}

	return -1;
}

WorldPacket* BufferPool::Allocate(size_t sz)
{
	int8 bufPool = GetBufferPool(sz);
	if( bufPool == -1 )
		return new WorldPacket(0, sz);

	WorldPacket *ret;
	m_buckets[bufPool]->m_lock.Acquire();
	ret = m_buckets[bufPool]->m_bucket->Dequeue();
	m_buckets[bufPool]->m_lock.Release();
	return ret;
}

void BufferPool::Deallocate(WorldPacket *pck)
{
	if( pck->m_bufferPool == -1 )
	{
		SafeDelete(pck);
		return;
	}

	BufferBucketNode *b = m_buckets[pck->m_bufferPool];
	b->m_lock.Acquire();
	b->m_bucket->Queue(pck);
	b->m_lock.Release();
}

void BufferPool::Init()
{
	DEBUG_LOG("BufferPool::Init()\n");
	uint32 x;
	for( x = 0; x < BUFFER_BUCKET_COUNT; ++x )
		m_buckets[x] = new BufferBucketNode(new BufferBucket(*this, (BUFFERPOOL_BUCKET_SIZE)x));
}

void BufferPool::Destroy()
{
	DEBUG_LOG("BufferPool::Destroy()\n");
	uint32 x;
	for( x = 0; x < BUFFER_BUCKET_COUNT; ++x )
		SafeDelete(m_buckets[x]);
}

void BufferPool::Stats()
{
	DEBUG_LOG("BufferPool::Stats()\n");
	uint32 x;
	for( x = 0; x < BUFFER_BUCKET_COUNT; ++x )
	{
		m_buckets[x]->m_lock.Acquire();
		m_buckets[x]->m_bucket->Stats();
		m_buckets[x]->m_lock.Release();
	}
}

void BufferPool::Optimize()
{
	DEBUG_LOG("BufferPool::Optimize()\n");
	uint32 x;
	for( x = 0; x < BUFFER_BUCKET_COUNT; ++x )
	{
		m_buckets[x]->m_lock.Acquire();
		m_buckets[x]->m_bucket->Optimize();
		m_buckets[x]->m_lock.Release();
	}
}

BufferPool g_bufferPool;

#endif