
#include <thrift/machine.h>

#ifndef __THRIFT_INIT_H__
#define __THRIFT_INIT_H__

#if defined TN_COMPILER_MSVC

/*
 * Automatic constructors are not yet officially supported in MSVC, however,
 * there is a similar feature where functions in the ".CRT$XCU" section are
 * evaluated prior to DllMain(), main() and friends.
 *
 * See http://blogs.msdn.com/b/vcblog/archive/2006/10/20/crt-initialization.aspx
 * for more information.
 */
# define TN_BOOTSTRAP_FUNC(func) \
	static void __cdecl func(void);	\
	__declspec(allocate(".CRT$XCU")) void(__cdecl * func##_) (void) = func;	\
	static void __cdecl func(void)
#elif defined TN_COMPILER_GCC_COMPAT
# if TN_COMPILER_GCC_VERSION >= 403000
#  define TN_BOOTSTRAP_FUNC(func) \
	static void func(void) __attribute__((cold, constructor, flatten)); \
	static void func(void)
# else
#  define TN_BOOTSTRAP_FUNC(func) \
	static void func(void) __attribute__((constructor, flatten)); \
	static void func(void)
# endif
#else
# error TN_BOOTSTRAP_FUNC not implemented for your platform :(
#endif

#endif