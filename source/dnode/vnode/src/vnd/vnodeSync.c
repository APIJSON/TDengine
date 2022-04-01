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

#include "vnodeSync.h"
#include "vnd.h"

int32_t vnodeSyncOpen(SVnode *pVnode) {
  SSyncInfo syncInfo;

  syncInfo.vgId = pVnode->vgId;
  SSyncCfg *pCfg = &(syncInfo.syncCfg);
  pCfg->replicaNum = pVnode->config.syncCfg.replicaNum;
  pCfg->myIndex = pVnode->config.syncCfg.myIndex;
  memcpy(pCfg->nodeInfo, pVnode->config.syncCfg.nodeInfo, sizeof(pCfg->nodeInfo));

  snprintf(syncInfo.path, sizeof(syncInfo.path), "%s/sync", pVnode->path);
  syncInfo.pWal = pVnode->pWal;

  syncInfo.pFsm = NULL;
  syncInfo.rpcClient = NULL;
  syncInfo.FpSendMsg = NULL;
  syncInfo.queue = NULL;
  syncInfo.FpEqMsg = NULL;

  pVnode->sync = syncStart(&syncInfo);
  assert(pVnode->sync > 0);

  return 0;
}

void vnodeSyncClose(SVnode *pVnode) {
  // stop by ref id
  syncStop(pVnode->sync);
}