#pragma once

namespace internal
{
	template <unsigned int N, unsigned int I>
	struct StringHashGenerator
	{
		inline static StringHash::Type Hash(const char (&str)[N])
		{
			return (StringHashGenerator<N, I-1>::Hash(str) ^ str[I-1])*16777619u;
		}
	};


	/// \brief Partial template specialization ending the recursion of Hash() function calls.
	template <unsigned int N>
	struct StringHashGenerator<N, 1>
	{
		/// Function generating the hash value for the first character in the given string literal.
		ME_INLINE static StringHash::Type Hash(const char (&str)[N])
		{
			return (2166136261u ^ str[0])*16777619u;
		}
	};


	/// \brief Partial template specialization prohibiting the hashing of empty string literals.
	template <unsigned int N>
	struct StringHashGenerator<N, 0>
	{
		/// Function prohibiting the hashing of empty string literals.
		static StringHash::Type Hash(const char (&str)[N])
		{
			static_assert(false, "Empty constant strings cannot be hashed.");
		}
	};


	/// Type that represents the outcome of a compile-time value for any other type than a string literal.
	typedef compileTime::IntToType<false> NonStringLiteral;

	/// Type that represents the outcome of a compile-time value for a string literal type.
	typedef compileTime::IntToType<true> StringLiteral;


	/// \brief Generates a hash for constant strings/string literals.
	/// \remark The StringLiteral argument is never used, and serves only as a type used in overload resolution
	/// in the type-based dispatch mechanism.
	template <size_t N>
	ME_INLINE StringHash::Type GenerateHash(const char (&str)[N], StringLiteral)
	{
		// defer the hash generation to the template mechanism
		return StringHashGenerator<N, N-1>::Hash(str);
	}


	/// \brief Generates a hash for non-constant strings.
	/// \remark The NonStringLiteral argument is never used, and serves only as a type used in overload resolution
	/// in the type-based dispatch mechanism.
	inline StringHash::Type GenerateHash(const char* str, NonStringLiteral)
	{
		return hashing::Fnv1aHash(str, strlen(str));
	}
}