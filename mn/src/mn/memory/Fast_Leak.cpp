#include "mn/memory/Fast_Leak.h"
#include "mn/Context.h"

#include <stdio.h>
#include <stdlib.h>

namespace mn::memory
{
	Fast_Leak::Fast_Leak()
	{
		this->atomic_size = 0;
		this->atomic_count = 0;
	}

	Fast_Leak::~Fast_Leak()
	{
		if(this->atomic_count > 0)
		{
			::fprintf(
				stderr,
				"Leaks count: %zu, Leaks size(bytes): %zu, for callstack turn on 'MN_LEAK' flag\n",
				atomic_count.load(),
				atomic_size.load()
			);
			::fprintf(stderr, "Press any key to continue...\n");
			::getchar();
		}
	}

	Block
	Fast_Leak::alloc(size_t size, uint8_t)
	{
		Block res {::malloc(size), size};
		memory_profile_alloc(res.ptr, res.size);
		if(res)
		{
			atomic_count.fetch_add(1);
			atomic_size.fetch_add(size);
			return res;
		}
		return {};
	}

	void
	Fast_Leak::free(Block block)
	{
		if(block)
		{
			atomic_count.fetch_sub(1);
			atomic_size.fetch_sub(block.size);
		}
		memory_profile_free(block.ptr, block.size);
		::free(block.ptr);
	}

	Fast_Leak*
	fast_leak()
	{
		static Fast_Leak _leak_allocator;
		return &_leak_allocator;
	}
}