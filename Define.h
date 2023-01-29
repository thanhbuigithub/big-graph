//
// Created by Bui Chi Thanh on 18/01/2023.
//

#ifndef BIGGRAPH_DEFINE_H
#define BIGGRAPH_DEFINE_H

#include <string>
#include <stdexcept>
#include <memory>

// Messages
void notify(const char* title, const char* message);
void errorLog(const char* message);
template<typename ... Args>
std::string string_format( const std::string& format, Args ... args )
{
    int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    auto size = static_cast<size_t>( size_s );
    std::unique_ptr<char[]> buf( new char[ size ] );
    std::snprintf( buf.get(), size, format.c_str(), args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}

#define INFORMATION_DEBUG "Information"
#define WARNING_DEBUG "Warning"
#define ERROR_DEBUG "Error"

inline void InfoNotify(const char* message){ notify(INFORMATION_DEBUG, message); }
inline void WarnNotify(const char* message){ notify(WARNING_DEBUG, message); }
inline void ErrNotify(const char* message){ notify(ERROR_DEBUG, message);}

// Assertions
void ExeStop(
        const char* message, const char* reason,
        const char* condition, const char* file, const int& line);
#define Fail ExeStop(NULL, NULL, "Fail", __FILE__, __LINE__)
#define FailR(Reason) ExeStop((Reason), NULL, "Fail", __FILE__, __LINE__)

#define IAssertM(Message) InfoNotify(Message)

#define IAssert(Cond, Message) \
  ((Cond) ? InfoNotify(Message) : static_cast<void>(0))

#define WAssert(Cond, Message) \
  ((Cond) ? WarnNotify(Message) : static_cast<void>(0))

#define EAssert(Cond) \
  ((Cond) ? ExeStop(NULL, NULL, #Cond, __FILE__, __LINE__) : static_cast<void>(0))

#define EAssertR(Cond, Reason) \
  ((Cond) ? ExeStop(NULL, Reason, #Cond, __FILE__, __LINE__) : static_cast<void>(0))
#endif //BIGGRAPH_DEFINE_H
