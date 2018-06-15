#ifndef AFS_SHA1_H
#define AFS_SHA1_H

/*****************************************************************************
**
**  Definition of the SHA1 files checksum interface
**
**  Creation date:  2016/11/09
**  Created by:     Piql AS
**
**
**  Copyright (c) 2014 Piql AS. All rights reserved.
**
**  This file is part of the boxing library
**
*****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "boxing/platform/types.h"

int   afs_sha1_test(void);
char* afs_sha1_sum1(const char* file_name);
char* afs_sha1_sum2(const char* file_name, boxing_int64 start, boxing_int64 size);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // AFS_SHA1_H
