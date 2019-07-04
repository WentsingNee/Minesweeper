//
// Created by peter on 19-5-20.
//

#ifndef LOG_HPP
#define LOG_HPP


#include <android/log.h>
#include <sstream>
#include <boost/current_function.hpp>

template <typename Tp>
void multi_args_write(std::ostream & log_fp, Tp && arg0)
{
    log_fp << arg0;
}

template <typename Tp, typename ...Up>
void multi_args_write(std::ostream & log_fp, Tp && arg0, Up&& ...args)
{
    log_fp << arg0;
    multi_args_write(log_fp, std::forward<Up>(args)...);
}

template <android_LogPriority level, typename ...T>
void log_write(const char *source_filename, const char * current_function, int line, T&& ... args) noexcept
{
    std::ostringstream buffer;
    multi_args_write(buffer, source_filename, ": ", line, ": ", current_function, " ", std::forward<T>(args)...);

    __android_log_print(level, "keymatch", "%s\n", buffer.str().c_str());
//#define LOGD(fmt, ...) __android_log_print(ANDROID_LOG_DEBUG, "keymatch", fmt, __VA_ARGS__)
//#define LOGE(fmt, ...) __android_log_print(ANDROID_LOG_ERROR, "keymatch", fmt, __VA_ARGS__)
//#define LOGF(fmt, ...) __android_log_print(ANDROID_LOG_FATAL, "keymatch", fmt, __VA_ARGS__)
//#define LOGW(fmt, ...) __android_log_print(ANDROID_LOG_WARN, "keymatch", fmt, __VA_ARGS__)

}

#ifndef LOG_DEBUG
#   define LOG_DEBUG(x...) \
	    log_write<ANDROID_LOG_DEBUG>(__FILE__, BOOST_CURRENT_FUNCTION, __LINE__, ##x)
#endif

#ifndef LOG_INFO
#   define LOG_INFO(x...) \
	    log_write<ANDROID_LOG_INFO>(__FILE__, BOOST_CURRENT_FUNCTION, __LINE__, ##x)
#endif

#ifndef LOG_WARNING
#   define LOG_WARNING(x...)	 \
	    log_write<ANDROID_LOG_WARN>(__FILE__, BOOST_CURRENT_FUNCTION, __LINE__, ##x)
#endif

#ifndef LOG_FATAL
#   define LOG_FATAL(x...) \
	    log_write<ANDROID_LOG_FATAL>(__FILE__, BOOST_CURRENT_FUNCTION, __LINE__, ##x)
#endif

#endif //LOG_HPP
