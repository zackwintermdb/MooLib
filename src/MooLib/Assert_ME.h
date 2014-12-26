#pragma once

/*
	Copyright (c) 2011, Stefan Reinalter

	This software is provided 'as-is', without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1. The origin of this software must not be misrepresented; you must not
	claim that you wrote the original software. If you use this software
	in a product, an acknowledgment in the product documentation would be
	appreciated but is not required.

	2. Altered source versions must be plainly marked as such, and must not be
	misrepresented as being the original software.

	3. This notice may not be removed or altered from any source
	distribution.
*/


/// concatenates tokens, even when the tokens are macros themselves
#define ME_PP_JOIN_HELPER_HELPER(_0, _1)		_0##_1
#define ME_PP_JOIN_HELPER(_0, _1)				ME_PP_JOIN_HELPER_HELPER(_0, _1)
#define ME_PP_JOIN_IMPL(_0, _1)					ME_PP_JOIN_HELPER(_0, _1)

#define ME_PP_JOIN_2(_0, _1)																	ME_PP_JOIN_IMPL(_0, _1)
#define ME_PP_JOIN_3(_0, _1, _2)																ME_PP_JOIN_2(ME_PP_JOIN_2(_0, _1), _2)
#define ME_PP_JOIN_4(_0, _1, _2, _3)															ME_PP_JOIN_2(ME_PP_JOIN_3(_0, _1, _2), _3)
#define ME_PP_JOIN_5(_0, _1, _2, _3, _4)														ME_PP_JOIN_2(ME_PP_JOIN_4(_0, _1, _2, _3), _4)
#define ME_PP_JOIN_6(_0, _1, _2, _3, _4, _5)													ME_PP_JOIN_2(ME_PP_JOIN_5(_0, _1, _2, _3, _4), _5)
#define ME_PP_JOIN_7(_0, _1, _2, _3, _4, _5, _6)												ME_PP_JOIN_2(ME_PP_JOIN_6(_0, _1, _2, _3, _4, _5), _6)
#define ME_PP_JOIN_8(_0, _1, _2, _3, _4, _5, _6, _7)											ME_PP_JOIN_2(ME_PP_JOIN_7(_0, _1, _2, _3, _4, _5, _6), _7)
#define ME_PP_JOIN_9(_0, _1, _2, _3, _4, _5, _6, _7, _8)										ME_PP_JOIN_2(ME_PP_JOIN_8(_0, _1, _2, _3, _4, _5, _6, _7), _8)
#define ME_PP_JOIN_10(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9)									ME_PP_JOIN_2(ME_PP_JOIN_9(_0, _1, _2, _3, _4, _5, _6, _7, _8), _9)
#define ME_PP_JOIN_11(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10)								ME_PP_JOIN_2(ME_PP_JOIN_10(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9), _10)
#define ME_PP_JOIN_12(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11)							ME_PP_JOIN_2(ME_PP_JOIN_11(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10), _11)
#define ME_PP_JOIN_13(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12)					ME_PP_JOIN_2(ME_PP_JOIN_12(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11), _12)
#define ME_PP_JOIN_14(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13)				ME_PP_JOIN_2(ME_PP_JOIN_13(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12), _13)
#define ME_PP_JOIN_15(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14)			ME_PP_JOIN_2(ME_PP_JOIN_14(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13), _14)
#define ME_PP_JOIN_16(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15)		ME_PP_JOIN_2(ME_PP_JOIN_15(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14), _15)


/// chooses a value based on a condition
#define ME_PP_IF_0(t, f)			f
#define ME_PP_IF_1(t, f)			t
#define ME_PP_IF(cond, t, f)		ME_PP_JOIN_2(ME_PP_IF_, ME_PP_TO_BOOL(cond))(t, f)


/// converts a condition into a boolean 0 (=false) or 1 (=true)
#define ME_PP_TO_BOOL_0 0
#define ME_PP_TO_BOOL_1 1
#define ME_PP_TO_BOOL_2 1
#define ME_PP_TO_BOOL_3 1
#define ME_PP_TO_BOOL_4 1
#define ME_PP_TO_BOOL_5 1
#define ME_PP_TO_BOOL_6 1
#define ME_PP_TO_BOOL_7 1
#define ME_PP_TO_BOOL_8 1
#define ME_PP_TO_BOOL_9 1
#define ME_PP_TO_BOOL_10 1
#define ME_PP_TO_BOOL_11 1
#define ME_PP_TO_BOOL_12 1
#define ME_PP_TO_BOOL_13 1
#define ME_PP_TO_BOOL_14 1
#define ME_PP_TO_BOOL_15 1
#define ME_PP_TO_BOOL_16 1

#define ME_PP_TO_BOOL(x)		ME_PP_JOIN_2(ME_PP_TO_BOOL_, x)


/// Returns 1 if the arguments to the variadic macro are separated by a comma, 0 otherwise.
#define ME_PP_HAS_COMMA(...)							ME_PP_HAS_COMMA_EVAL(ME_PP_HAS_COMMA_ARGS(__VA_ARGS__, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0))
#define ME_PP_HAS_COMMA_EVAL(...)						__VA_ARGS__
#define ME_PP_HAS_COMMA_ARGS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, ...) _16


/// Returns 1 if the argument list to the variadic macro is empty, 0 otherwise.
#define ME_PP_IS_EMPTY(...)														\
	ME_PP_HAS_COMMA																\
	(																			\
		ME_PP_JOIN_5															\
		(																		\
			ME_PP_IS_EMPTY_CASE_,												\
			ME_PP_HAS_COMMA(__VA_ARGS__),										\
			ME_PP_HAS_COMMA(ME_PP_IS_EMPTY_BRACKET_TEST __VA_ARGS__),			\
			ME_PP_HAS_COMMA(__VA_ARGS__ (~)),									\
			ME_PP_HAS_COMMA(ME_PP_IS_EMPTY_BRACKET_TEST __VA_ARGS__ (~))		\
		)																		\
	)

#define ME_PP_IS_EMPTY_CASE_0001			,
#define ME_PP_IS_EMPTY_BRACKET_TEST(...)	,


// ME_PP_VA_NUM_ARGS() is a very nifty macro to retrieve the number of arguments handed to a variable-argument macro.
// unfortunately, VS 2010 still has this preprocessor bug which treats a __VA_ARGS__ argument as being one single parameter:
// https://connect.microsoft.com/VisualStudio/feedback/details/521844/variadic-macro-treating-va-args-as-a-single-parameter-for-other-macros#details
#if _MSC_VER >= 1400
#	define ME_PP_VA_NUM_ARGS_HELPER(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, N, ...)	N
#	define ME_PP_VA_NUM_ARGS_REVERSE_SEQUENCE			16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1
#	define ME_PP_VA_NUM_ARGS_LEFT (
#	define ME_PP_VA_NUM_ARGS_RIGHT )
#	define ME_PP_VA_NUM_ARGS(...)						ME_PP_VA_NUM_ARGS_HELPER ME_PP_VA_NUM_ARGS_LEFT __VA_ARGS__, ME_PP_VA_NUM_ARGS_REVERSE_SEQUENCE ME_PP_VA_NUM_ARGS_RIGHT
#else
#	define ME_PP_VA_NUM_ARGS(...)						ME_PP_VA_NUM_ARGS_HELPER(__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#	define ME_PP_VA_NUM_ARGS_HELPER(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, N, ...)	N
#endif

// ME_PP_NUM_ARGS correctly handles the case of 0 arguments
#define ME_PP_NUM_ARGS(...)								ME_PP_IF(ME_PP_IS_EMPTY(__VA_ARGS__), 0, ME_PP_VA_NUM_ARGS(__VA_ARGS__))


// ME_PP_PASS_ARGS passes __VA_ARGS__ as multiple parameters to another macro, working around the following bug:
// https://connect.microsoft.com/VisualStudio/feedback/details/521844/variadic-macro-treating-va-args-as-a-single-parameter-for-other-macros#details
#if _MSC_VER >= 1400
#	define ME_PP_PASS_ARGS_LEFT (
#	define ME_PP_PASS_ARGS_RIGHT )
#	define ME_PP_PASS_ARGS(...)							ME_PP_PASS_ARGS_LEFT __VA_ARGS__ ME_PP_PASS_ARGS_RIGHT
#else
#	define ME_PP_PASS_ARGS(...)							(__VA_ARGS__)
#endif


/// Expand any number of arguments into a list of operations called with those arguments
#define ME_PP_EXPAND_ARGS_0(op, empty)
#define ME_PP_EXPAND_ARGS_1(op, a1)																			op(a1, 0)
#define ME_PP_EXPAND_ARGS_2(op, a1, a2)																		op(a1, 0) op(a2, 1)
#define ME_PP_EXPAND_ARGS_3(op, a1, a2, a3)																	op(a1, 0) op(a2, 1) op(a3, 2)
#define ME_PP_EXPAND_ARGS_4(op, a1, a2, a3, a4)																op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3)
#define ME_PP_EXPAND_ARGS_5(op, a1, a2, a3, a4, a5)															op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4)
#define ME_PP_EXPAND_ARGS_6(op, a1, a2, a3, a4, a5, a6)														op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5)
#define ME_PP_EXPAND_ARGS_7(op, a1, a2, a3, a4, a5, a6, a7)													op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5) op(a7, 6)
#define ME_PP_EXPAND_ARGS_8(op, a1, a2, a3, a4, a5, a6, a7, a8)												op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5) op(a7, 6) op(a8, 7)
#define ME_PP_EXPAND_ARGS_9(op, a1, a2, a3, a4, a5, a6, a7, a8, a9)											op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5) op(a7, 6) op(a8, 7) op(a9, 8)
#define ME_PP_EXPAND_ARGS_10(op, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10)									op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5) op(a7, 6) op(a8, 7) op(a9, 8) op(a10, 9)
#define ME_PP_EXPAND_ARGS_11(op, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11)								op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5) op(a7, 6) op(a8, 7) op(a9, 8) op(a10, 9) op(a11, 10)
#define ME_PP_EXPAND_ARGS_12(op, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12)							op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5) op(a7, 6) op(a8, 7) op(a9, 8) op(a10, 9) op(a11, 10) op(a12, 11)
#define ME_PP_EXPAND_ARGS_13(op, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13)					op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5) op(a7, 6) op(a8, 7) op(a9, 8) op(a10, 9) op(a11, 10) op(a12, 11) op(a13, 12)
#define ME_PP_EXPAND_ARGS_14(op, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14)				op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5) op(a7, 6) op(a8, 7) op(a9, 8) op(a10, 9) op(a11, 10) op(a12, 11) op(a13, 12) op(a14, 13)
#define ME_PP_EXPAND_ARGS_15(op, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15)			op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5) op(a7, 6) op(a8, 7) op(a9, 8) op(a10, 9) op(a11, 10) op(a12, 11) op(a13, 12) op(a14, 13) op(a15, 14)
#define ME_PP_EXPAND_ARGS_16(op, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16)		op(a1, 0) op(a2, 1) op(a3, 2) op(a4, 3) op(a5, 4) op(a6, 5) op(a7, 6) op(a8, 7) op(a9, 8) op(a10, 9) op(a11, 10) op(a12, 11) op(a13, 12) op(a14, 13) op(a15, 14) op(a16, 15)

#define ME_PP_EXPAND_ARGS(op, ...)		ME_PP_JOIN_2(ME_PP_EXPAND_ARGS_, ME_PP_NUM_ARGS(__VA_ARGS__)) ME_PP_PASS_ARGS(op, __VA_ARGS__)


/// Turns any legal C++ expression into nothing
#define ME_UNUSED_IMPL(symExpr, n)					, (void)sizeof(symExpr)
#define ME_UNUSED(...)								(void)sizeof(true) ME_PP_EXPAND_ARGS ME_PP_PASS_ARGS(ME_UNUSED_IMPL, __VA_ARGS__)


/// Breaks into the debugger (if it is attached)
#if !ME_MASTER
#	define ME_BREAKPOINT								((IsDebuggerPresent() != 0) ? __debugbreak() : ME_UNUSED(true))
#else
#	define ME_BREAKPOINT								ME_UNUSED(true)
#endif
