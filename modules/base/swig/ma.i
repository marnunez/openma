/* 
 * Open Source Movement Analysis Library
 * Copyright (C) 2016, Moveck Solution Inc., all rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *     * Redistributions of source code must retain the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *     * Neither the name(s) of the copyright holders nor the names
 *       of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written
 *       permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

%module ma

%begin %{
#include "openma/matlab/fixwinchar16.h"
%}

%{
#include "openma/base.h"
#include "openma/bindings.h"
%}

%init %{
  // Redirect OpenMA error message
  ma::Logger::setDevice(new ma::bindings::LoggerDevice);
%}

%include "macros.i"

%include <std_string.i>

%exception {
  auto logdev = static_cast<ma::bindings::LoggerDevice*>(ma::Logger::device());
  logdev->clearError();
  $action
  if (logdev->errorFlag())
  {
    SWIG_exception_fail(SWIG_RuntimeError, logdev->errorMessage().c_str());
  }
}

// ========================================================================= //
//                                INTERFACE
// ========================================================================= //

// Use a single threaded reference counting mechanism to release the data
%feature("ref", noblock=1) ma::Node {_ma_refcount_incr($this);};
%feature("unref", noblock=1) ma::Node {_ma_refcount_decr($this);};

#if defined(SWIGMATLAB)
%include "ma_matlab.i"
#elif defined(SWIGPYTHON)
%include "ma_python.i"
#endif

%include "../include/openma/base/enums.h"

%include "base/any.i"
%include "base/object.i"
%include "base/node.i"
%include "base/event.i"
%include "base/subject.i"
%include "base/timesequence.i"
%include "base/trial.i"
%include "base/logger.i"
%include "base/hardware.i"