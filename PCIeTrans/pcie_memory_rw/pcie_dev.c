#ifdef __cplusplus
extern "C" {
#endif

#include "pcie_dev.h"

#pragma comment(lib, "setupapi.lib")

#define ONE_MB (1024UL * 1024UL)

/* helper struct to remember the Xdma device names */
typedef struct {
    TCHAR base_path[MAX_PATH + 1];  /* path to first found Xdma device */
    uint16_t * buffer_c2h;   /* pointer to the allocated buffer card to host*/
    uint16_t * buffer_h2c;   /* pointer to the allocated buffer host to card*/
    DWORD buf_c2h_size; /* size of the buffer c2h in bytes */
    DWORD buf_h2c_size; /* size of the buffer h2c in bytes */
    HANDLE c2h0;
    HANDLE h2c0;
} xdma_device;

xdma_device xdma;

//查找XDMA设备
static DWORD find_devices(GUID guid, PTCHAR devpath, size_t len_devpath)
{

    HDEVINFO device_info = SetupDiGetClassDevs((LPGUID)&guid, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
    if (device_info == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "GetDevices INVALID_HANDLE_VALUE\n");
        exit(-1);
    }

    SP_DEVICE_INTERFACE_DATA device_interface;
    device_interface.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

    // enumerate through devices
    DWORD index;
    for (index = 0; SetupDiEnumDeviceInterfaces(device_info, NULL, &guid, index, &device_interface); ++index) {

        // get required buffer size
        ULONG detailLength = 0;
        if (!SetupDiGetDeviceInterfaceDetail(device_info, &device_interface, NULL, 0,
                                             &detailLength, NULL) && GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
            fprintf(stderr, "SetupDiGetDeviceInterfaceDetail - get length failed\n");
            break;
        }

        // allocate space for device interface detail
        PSP_DEVICE_INTERFACE_DETAIL_DATA dev_detail = (PSP_DEVICE_INTERFACE_DETAIL_DATA)HeapAlloc(GetProcessHeap(),
                                                                                                  HEAP_ZERO_MEMORY, detailLength);
        if (!dev_detail) {
            fprintf(stderr, "HeapAlloc failed\n");
            break;
        }
        dev_detail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

        // get device interface detail
        if (!SetupDiGetDeviceInterfaceDetail(device_info, &device_interface, dev_detail, detailLength, NULL, NULL)) {
            fprintf(stderr, "SetupDiGetDeviceInterfaceDetail - get detail failed\n");
            HeapFree(GetProcessHeap(), 0, dev_detail);
            break;
        }

        StringCchCopy(devpath, len_devpath, dev_detail->DevicePath);
        HeapFree(GetProcessHeap(), 0, dev_detail);
    }

    SetupDiDestroyDeviceInfoList(device_info);

    return index;
}

//初始化PCIe
int pcie_init()
{
    int status = 1;

    // get device path from GUID
    DWORD num_devices = find_devices(GUID_DEVINTERFACE_XDMA, &xdma.base_path[0], sizeof(xdma.base_path));
    printf("Found %lu Xdma device%s.\n", num_devices, num_devices == 1 ? "" : "s");
    if (num_devices < 1)
        status = -1;

    /* allocate buffer */
    xdma.buf_c2h_size = ONE_MB; // buffer card to host size
    xdma.buffer_c2h = _aligned_malloc(xdma.buf_c2h_size, 1024); //512 | 1024
    if (!xdma.buffer_c2h) {
        status = -1;
        fprintf(stderr, "Error allocate buffer , error code: %lu@\n", GetLastError());
    }
    return status;
}

HANDLE open_device(TCHAR * device_name, TCHAR * base_path, DWORD dwDesiredAccess)
{
    HANDLE device;
    TCHAR device_path[MAX_PATH + 1];

    _tcscpy_s(device_path, sizeof device_path, base_path);
    _tcscat_s(device_path, sizeof device_path, device_name);

    /* open XDMA device */
    device = CreateFile(device_path, dwDesiredAccess,
                           0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    return device;
}

//打开PCIe设备
int pcie_open()
{
    int status = 1;

    /* open XDMA Host-to-Card 0 device */
    xdma.h2c0 = open_device(XDMA_FILE_H2C_0, xdma.base_path, GENERIC_READ | GENERIC_WRITE);
    if (xdma.h2c0 == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Error opening device, win64 error code: %lu\n", GetLastError());
        _tprintf(L"Error opening device, xdma.base_path: %s@\n",xdma.base_path);
        status = -1;
        goto cleanup_handles;
    }

    /* open XDMA Card-to-Host 0 device */
    xdma.c2h0 = open_device(XDMA_FILE_C2H_0, xdma.base_path, GENERIC_READ | GENERIC_WRITE);
    if (xdma.c2h0 == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Error opening device, win64 error code: %lu@\n", GetLastError());
        status = -1;
        goto cleanup_handles;
    }

    return status;

cleanup_handles:
    if (xdma.c2h0) CloseHandle(xdma.c2h0);
    if (xdma.h2c0) CloseHandle(xdma.h2c0);
    return status;
}

//关闭PCIe设备
void pcie_close()
{
    if (xdma.c2h0) CloseHandle(xdma.c2h0);
    if (xdma.h2c0) CloseHandle(xdma.h2c0);
    if (xdma.buffer_c2h) _aligned_free(xdma.buffer_c2h);
    if (xdma.buffer_h2c) _aligned_free(xdma.buffer_h2c);
}

static long write_device(HANDLE device, long offset, unsigned long size, uint16_t* snd_content)
{
    DWORD count = 0;

    if (INVALID_SET_FILE_POINTER == SetFilePointer(device, offset, NULL, FILE_BEGIN)) {
        fprintf(stderr, "Error setting file pointer, error code: %ld\n", GetLastError());
        return -1;
    }

    // write to device from allocated buffer
    if (!WriteFile(device, snd_content, size * sizeof(uint16_t), &count, NULL)) {
        fprintf(stderr, "WriteFile to device failed with Win64 error code: %ld\n",
                GetLastError());
        return -1;
    }

    return count / sizeof(uint16_t);
}

static long read_device(HANDLE device, long offset, unsigned long size, uint16_t* rcv_content)
{
    DWORD count=0;

    if (INVALID_SET_FILE_POINTER == SetFilePointer(device, offset, NULL, FILE_BEGIN)) {
        fprintf(stderr, "Error setting file pointer, error code: %ld\n", GetLastError());
        return -1;
    }

    // read from device into allocated buffer
    if (!ReadFile(device, rcv_content, size * sizeof(uint16_t), &count, NULL)) {
        fprintf(stderr, "ReadFile from device failed with Win64 error code: %ld\n",
                GetLastError());
        return -1;
    }

    return count / sizeof(uint16_t);
}

//transfer data from Host PC to FPGA Card
long h2c_transfer(long offset, unsigned long size, uint16_t* snd_content)
{
    return write_device(xdma.h2c0, offset, size, snd_content);
}

//transfer data from FPGA Card to Host PC
long c2h_transfer(long offset, unsigned long size, uint16_t* rcv_content)
{
    if(size < 5){
        read_device(xdma.c2h0, offset, 10, xdma.buffer_c2h);
        memcpy_s(rcv_content, sizeof (rcv_content), xdma.buffer_c2h, size);
        return size;
    }
    else
        return read_device(xdma.c2h0, offset, size, rcv_content);
}

#ifdef __cplusplus
}
#endif
