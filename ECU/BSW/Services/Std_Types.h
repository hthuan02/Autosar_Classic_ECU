#ifndef STD_TYPES_H
#define STD_TYPES_H

#include <stdint.h>

/* Boolean Data Types */
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

/* Standard Return Type */
typedef uint8_t Std_ReturnType;

#define E_OK        0x00U  /* Operation successful */
#define E_NOT_OK    0x01U  /* Operation not successful */

/* Null Pointer Definition */
#define NULL_PTR    ((void*)0)

/* Standard Version Information Data Type */
typedef struct {
    uint16_t vendorID;
    uint16_t moduleID;
    uint8_t  sw_major_version;
    uint8_t  sw_minor_version;
    uint8_t  sw_patch_version;
} Std_VersionInfoType;

#endif /* STD_TYPES_H */
