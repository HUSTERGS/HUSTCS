/*
   Filter.h
   Copyright (c) 1989 Borland International, Inc.
   All rights reserved.
*/

#if !defined(__FILTER__)
#define __FILTER__

#define PipeId          "BI#PIP#OK"
#define PipeIdLen       10

typedef enum MsgType {
  MsgNewFile,
  MsgNewLine,
  MsgEoFile = 0x007F,
} MsgType;

#endif /* __FILTER__ */

