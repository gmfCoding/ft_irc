#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <sstream>

namespace IRCUtil
{
    template <typename T>
    std::string NumberToString ( T Number )
    {
        std::ostringstream ss;
        ss << Number;
        return ss.str();
    }
}
#endif