#pragma once

#include "mn/Assert.h"

namespace mn
{
	/**
	* @brief      A Fixed_Buf is a buffer with fixed capacity
	*
	* @tparam     T         Element type
	* @tparam     Capacity  Capacity of the fixed buffer
	*/
	template<typename T, size_t Capacity>
	struct Fixed_Buf
	{
		size_t count;
		T elements[Capacity];

		T&
		operator[](size_t ix)
		{
			mn_assert(ix < count);
			return elements[ix];
		}

		const T&
		operator[](size_t ix) const
		{
			mn_assert(ix < count);
			return elements[ix];
		}
	};

	/**
	* @brief      Creates a new fixed_buf with fixed capacity
	*/
	template<typename T, size_t Capacity>
	inline static Fixed_Buf<T, Capacity>
	fixed_buf_new()
	{
		Fixed_Buf<T, Capacity> self{};
		self.count = 0;
		return self;
	}

	/**
	* @brief      Pushes a new value to the given fixed_buf
	*
	* @param      self   The fixed_buf
	* @param[in]  value  The value to be pushed
	*
	*/
	template<typename T, size_t Capacity>
	inline static void
	fixed_buf_push(Fixed_Buf<T, Capacity>& self, const T& value)
	{
		mn_assert(self.count < Capacity);
		self.elements[self.count] = value;
		++self.count;
	}

	/**
	* @brief      Returns const pointer to the first element of the fixed_buf
	*/
	template<typename T, size_t Capacity>
	inline static const T*
	fixed_buf_begin(const Fixed_Buf<T, Capacity>& self)
	{
		return self.elements;
	}

	/**
	* @brief      Returns pointer to the first element of the fixed_buf
	*/
	template<typename T, size_t Capacity>
	inline static T*
	fixed_buf_begin(Fixed_Buf<T, Capacity>& self)
	{
		return self.elements;
	}

	/**
	* @brief      Returns const pointer to the last element of the fixed_buf
	*/
	template<typename T, size_t Capacity>
	inline static const T*
	fixed_buf_end(const Fixed_Buf<T, Capacity>& self)
	{
		return self.elements + self.count;
	}

	/**
	* @brief      Returns pointer to the last element of the fixed_buf
	*/
	template<typename T, size_t Capacity>
	inline static T*
	fixed_buf_end(Fixed_Buf<T, Capacity>& self)
	{
		return self.elements + self.count;
	}

	template<typename T, size_t Capacity>
	inline static const T*
	begin(const Fixed_Buf<T, Capacity>& self)
	{
		return fixed_buf_begin(self);
	}

	template<typename T, size_t Capacity>
	inline static T*
	begin(Fixed_Buf<T, Capacity>& self)
	{
		return fixed_buf_begin(self);
	}

	template<typename T, size_t Capacity>
	inline static const T*
	end(const Fixed_Buf<T, Capacity>& self)
	{
		return fixed_buf_end(self);
	}

	template<typename T, size_t Capacity>
	inline static T*
	end(Fixed_Buf<T, Capacity>& self)
	{
		return fixed_buf_end(self);
	}

}