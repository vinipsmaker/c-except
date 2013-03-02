////////////////////////////////////////////////////////////////////////////
// Copyright © 2010, Vinícius dos Santos Oliveira                         //
// All rights reserved.                                                   //
//                                                                        //
// Redistribution and use in source and binary forms, with or without     //
// modification, are permitted provided that the following conditions are //
// met:                                                                   //
//                                                                        //
//     * Redistributions of source code must retain the above copyright   //
//       notice, this list of conditions and the following disclaimer.    //
//                                                                        //
//     * Redistributions in binary form must reproduce the above          //
//       copyright notice, this list of conditions and the following      //
//       disclaimer in the documentation and/or other materials provided  //
//       with the distribution.                                           //
//                                                                        //
//     * Neither the name of the Massachusetts Institute of Technology    //
//       nor the names of its contributors may be used to endorse or      //
//       promote products derived from this software without specific     //
//       prior written permission.                                        //
//                                                                        //
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    //
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      //
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  //
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT   //
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  //
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT       //
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  //
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  //
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    //
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  //
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   //
////////////////////////////////////////////////////////////////////////////

#ifndef CEXCEPT_HANDL_H
#define CEXCEPT_HANDL_H

#ifdef __cplusplus

#include <cstdlib>
#include <cstring>
#include <csetjmp>

#else

#include <stdlib.h>
#include <string.h>
#include <setjmp.h>

#endif // __cplusplus

#define TRY(_id) \
  { \
    jmp_buf _eb ## _id; \
    struct _gvalue _ev ## _id [1] = {{NULL, NULL}}; \
    if (!setjmp(_eb ## _id)) {

#define CATCH(_type, _value, _id) \
    } else if (_ev ## _id->value \
               && _ev ## _id->name \
               && !strcmp(_ev ## _id->name, #_type)) { \
      _type _value = *((_type *)(_ev ## _id->value)); \
      _ev ## _id->name = NULL; \
      if (_ev ## _id->value) { \
        free(_ev ## _id->value); \
        _ev ## _id->value = NULL; \
      }

#define CATCHANY(_id) \
    } else { \
      _ev ## _id->name = NULL; \
      if (_ev ## _id->value) { \
        free(_ev ## _id->value); \
        _ev ## _id->value = NULL; \
      }

#define ENDTRY(_id) \
    } \
    if (_ev ## _id->value) free(_ev ## _id->value); \
  }

#define THROW(_type, _value, _id) \
  { \
    if (_ev ## _id) { \
      _ev ## _id->name = #_type; \
      _ev ## _id->value = malloc(sizeof(_type)); \
      *((_type *)(_ev ## _id->value)) = _value; \
    } \
    longjmp(_eb ## _id, 1); \
  }

#define THROWNOTHING(_id) longjmp(_eb ## _id, 1);

#define THROW_ARGS jmp_buf, struct _gvalue *const
#define THROW_NAMED_ARGS(_id) jmp_buf _eb ## _id, \
                              struct _gvalue *const _ev ## _id
#define TRY_ARGS(_id) _eb ## _id, _ev ## _id
#define TRY_VOID_ARGS(_id) _eb ## _id, NULL

struct _gvalue
{
  const char *name;
  void *value;
};

#endif // CEXCEPT_HANDL_H
