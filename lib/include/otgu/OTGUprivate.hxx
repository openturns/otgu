
#ifndef OTGU_PRIVATE_HXX
#define OTGU_PRIVATE_HXX

/* From http://gcc.gnu.org/wiki/Visibility */
/* Generic helper definitions for shared library support */
#if defined _WIN32 || defined __CYGWIN__
#define OTGU_HELPER_DLL_IMPORT __declspec(dllimport)
#define OTGU_HELPER_DLL_EXPORT __declspec(dllexport)
#define OTGU_HELPER_DLL_LOCAL
#else
#if __GNUC__ >= 4
#define OTGU_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
#define OTGU_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
#define OTGU_HELPER_DLL_LOCAL  __attribute__ ((visibility ("hidden")))
#else
#define OTGU_HELPER_DLL_IMPORT
#define OTGU_HELPER_DLL_EXPORT
#define OTGU_HELPER_DLL_LOCAL
#endif
#endif

/* Now we use the generic helper definitions above to define OTGU_API and OTGU_LOCAL.
 * OTGU_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
 * OTGU_LOCAL is used for non-api symbols. */

#ifndef OTGU_STATIC /* defined if OT is compiled as a DLL */
#ifdef OTGU_DLL_EXPORTS /* defined if we are building the OT DLL (instead of using it) */
#define OTGU_API OTGU_HELPER_DLL_EXPORT
#else
#define OTGU_API OTGU_HELPER_DLL_IMPORT
#endif /* OTGU_DLL_EXPORTS */
#define OTGU_LOCAL OTGU_HELPER_DLL_LOCAL
#else /* OTGU_STATIC is defined: this means OT is a static lib. */
#define OTGU_API
#define OTGU_LOCAL
#endif /* !OTGU_STATIC */


#endif // OTGU_PRIVATE_HXX

