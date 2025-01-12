// Copyright (c) 2018-2020 Simons Foundation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0.txt
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Authors: Olivier Parcollet, Nils Wentzell

#pragma once
#include <exception>
#include <string>
#include <sstream>
#include <cstdlib>

#define NDA_RUNTIME_ERROR throw nda::runtime_error{} << "Error at " << __FILE__ << " : " << __LINE__ << "\n\n"

#define NDA_ASSERT(X)                                                                                                                                \
  if (!(X)) NDA_RUNTIME_ERROR << AS_STRING(X);
#define NDA_ASSERT2(X, ...)                                                                                                                          \
  if (!(X)) NDA_RUNTIME_ERROR << AS_STRING(X) << "\n " << __VA_ARGS__;

namespace nda {

  class runtime_error : public std::exception {
    std::stringstream acc;
    std::string _trace;
    mutable std::string _what;

    public:
    runtime_error() noexcept : std::exception() {} // _trace = utility::stack_trace(); }

    runtime_error(runtime_error const &e) noexcept : acc(e.acc.str()), _trace(e._trace), _what(e._what) {}

    ~runtime_error() noexcept override = default;

    template <typename T>
    runtime_error &operator<<(T const &x) {
      acc << x;
      return *this;
    }

    runtime_error &operator<<(const char *mess) {
      (*this) << std::string(mess);
      return *this;
    } // to limit code size

    const char *what() const noexcept override {
      std::stringstream out;
      out << acc.str() << "\n.. Error occurred on node ";
      //if (mpi::is_initialized()) out << mpi::communicator().rank() << "\n";
      //if (getenv("NDA_SHOW_EXCEPTION_TRACE")) out << ".. C++ trace is : " << trace() << "\n";
      _what = out.str();
      return _what.c_str();
    }

    //virtual const char *trace() const noexcept { return _trace.c_str(); }
  };
} // namespace nda
