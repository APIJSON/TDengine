/*
 * Copyright (c) 2019 TAOS Data, Inc. <jhtao@taosdata.com>
 *
 * This program is free software: you can use, redistribute, and/or modify
 * it under the terms of the GNU Affero General Public License, version 3
 * or later ("AGPL"), as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _TD_TDB_H_
#define _TD_TDB_H_

#include "os.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct STDb       TDB;
typedef struct STDbEnv    TENV;
typedef struct STDbCurosr TDBC;

typedef int32_t pgsz_t;
typedef int32_t cachesz_t;

// TEVN
int tdbEnvCreate(TENV **ppEnv, const char *rootDir);
int tdbEnvOpen(TENV *ppEnv);
int tdbEnvClose(TENV *pEnv);

int tdbEnvBeginTxn(TENV *pEnv);
int tdbEnvCommit(TENV *pEnv);

int       tdbEnvSetCache(TENV *pEnv, pgsz_t pgSize, cachesz_t cacheSize);
pgsz_t    tdbEnvGetPageSize(TENV *pEnv);
cachesz_t tdbEnvGetCacheSize(TENV *pEnv);

// TDB
int tdbCreate(TDB **ppDb);
int tdbOpen(TDB **ppDb, const char *fname, const char *dbname, TENV *pEnv);
int tdbClose(TDB *pDb);

int tdbSetKeyLen(TDB *pDb, int klen);
int tdbSetValLen(TDB *pDb, int vlen);
int tdbSetDup(TDB *pDb, int dup);
int tdbGetKeyLen(TDB *pDb, int *pklen);
int tdbGetValLen(TDB *pDb, int *pvlen);
int tdbGetDup(TDB *pDb, int *pdup);

int tdbInsert(TDB *pDb, const void *pKey, int nKey, const void *pData, int nData);

// TDBC

#ifdef __cplusplus
}
#endif

#endif /*_TD_TDB_H_*/