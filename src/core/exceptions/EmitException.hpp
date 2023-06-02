#pragma once

#include "boost/exception/all.hpp"

namespace emit::core::exceptions {

typedef boost::error_info<struct tag_line, int> emit_exception_line;
typedef boost::error_info<struct tag_file, std::string> emit_exception_file;
typedef boost::error_info<struct tag_function, std::string>
    emit_exception_function;

class EmitException : virtual boost::exception, virtual std::exception {
  protected:
  public:
    EmitException(const std::string &message);
    virtual ~EmitException(){};
};

} // namespace emit::core::exceptions
