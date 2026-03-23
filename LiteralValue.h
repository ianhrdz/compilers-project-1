#pragma once

#include <variant>
#include <string>
#include <cstddef>

using LiteralValue = std::variant<
    std::monostate,   // no literal value
    double,           
    std::string,     
    bool,             
    std::nullptr_t    
>;