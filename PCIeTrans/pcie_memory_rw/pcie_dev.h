#ifndef PCIE_DEV_H
#define PCIE_DEV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <strsafe.h>
#include <stdint.h>
#include <tchar.h>
#include <Windows.h>
#include <SetupAPI.h>
#include <INITGUID.H>
#include <WinIoCtl.h>

#include "xdma_public.h"

int pcie_init();
int pcie_open();
void pcie_close();
long h2c_transfer(long offset, unsigned long size, uint16_t* snd_content);
long c2h_transfer(long offset, unsigned long size, uint16_t* rcv_content);

#ifdef __cplusplus
}
#endif

#endif // PCIE_DEV_H
