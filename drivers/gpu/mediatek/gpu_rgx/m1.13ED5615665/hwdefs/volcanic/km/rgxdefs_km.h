/*************************************************************************/ /*!
@Title          Rogue hw definitions (kernel mode)
@Copyright      Copyright (c) Imagination Technologies Ltd. All Rights Reserved
@License        Dual MIT/GPLv2

The contents of this file are subject to the MIT license as set out below.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

Alternatively, the contents of this file may be used under the terms of
the GNU General Public License Version 2 ("GPL") in which case the provisions
of GPL are applicable instead of those above.

If you wish to allow use of your version of this file only under the terms of
GPL, and not to allow others to use your version of this file under the terms
of the MIT license, indicate your decision by deleting the provisions above
and replace them with the notice and other provisions required by GPL as set
out in the file called "GPL-COPYING" included in this distribution. If you do
not delete the provisions above, a recipient may use your version of this file
under the terms of either the MIT license or GPL.

This License is also included in this distribution in the file called
"MIT-COPYING".

EXCEPT AS OTHERWISE STATED IN A NEGOTIATED AGREEMENT: (A) THE SOFTWARE IS
PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT; AND (B) IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/ /**************************************************************************/

#ifndef RGXDEFS_KM_H
#define RGXDEFS_KM_H

#if defined(RGX_BVNC_CORE_KM_HEADER) && defined(RGX_BNC_CONFIG_KM_HEADER)
#include RGX_BVNC_CORE_KM_HEADER
#include RGX_BNC_CONFIG_KM_HEADER
#endif

#define IMG_EXPLICIT_INCLUDE_HWDEFS
#if defined(__KERNEL__)
#include "rgx_cr_defs_km.h"
#endif
#undef IMG_EXPLICIT_INCLUDE_HWDEFS

#if !defined(SUPPORT_MULTIBVNC_RUNTIME_BVNC_ACQUISITION)
/******************************************************************************
 * Check for valid B.X.N.C
 *****************************************************************************/
#if !defined(RGX_BVNC_KM_B) || !defined(RGX_BVNC_KM_V) || !defined(RGX_BVNC_KM_N) || !defined(RGX_BVNC_KM_C)
#error "Need to specify BVNC (RGX_BVNC_KM_B, RGX_BVNC_KM_V, RGX_BVNC_KM_N and RGX_BVNC_C)"
#endif
#endif

/* Check core/config compatibility */
#if (RGX_BVNC_KM_B != RGX_BNC_KM_B) || (RGX_BVNC_KM_N != RGX_BNC_KM_N) || (RGX_BVNC_KM_C != RGX_BNC_KM_C)
#error "BVNC headers are mismatching (KM core/config)"
#endif

/******************************************************************************
 * RGX Version name
 *****************************************************************************/
#define RGX_BVNC_ST2(S)	#S
#define RGX_BVNC_ST(S)		RGX_BVNC_ST2(S)
#define RGX_BVNC_KM			RGX_BVNC_ST(RGX_BVNC_KM_B) "." RGX_BVNC_ST(RGX_BVNC_KM_V) "." RGX_BVNC_ST(RGX_BVNC_KM_N) "." RGX_BVNC_ST(RGX_BVNC_KM_C)
#define RGX_BVNC_KM_V_ST	RGX_BVNC_ST(RGX_BVNC_KM_V)

/* Maximum string size is [bb.vvvp.nnnn.cccc\0], includes null char */
#define RGX_BVNC_STR_SIZE_MAX (2+1+4+1+4+1+4+1)
#define RGX_BVNC_STR_FMTSPEC  "%u.%u.%u.%u"
#define RGX_BVNC_STRP_FMTSPEC "%u.%up.%u.%u"


/******************************************************************************
 * RGX Defines
 *****************************************************************************/

#define BVNC_FIELD_MASK     ((1 << BVNC_FIELD_WIDTH) - 1)
#define C_POSITION          (0)
#define N_POSITION          ((C_POSITION) + (BVNC_FIELD_WIDTH))
#define V_POSITION          ((N_POSITION) + (BVNC_FIELD_WIDTH))
#define B_POSITION          ((V_POSITION) + (BVNC_FIELD_WIDTH))

#define B_POSTION_MASK      (((IMG_UINT64)(BVNC_FIELD_MASK) << (B_POSITION)))
#define V_POSTION_MASK      (((IMG_UINT64)(BVNC_FIELD_MASK) << (V_POSITION)))
#define N_POSTION_MASK      (((IMG_UINT64)(BVNC_FIELD_MASK) << (N_POSITION)))
#define C_POSTION_MASK      (((IMG_UINT64)(BVNC_FIELD_MASK) << (C_POSITION)))

#define GET_B(x)            (((x) & (B_POSTION_MASK)) >> (B_POSITION))
#define GET_V(x)            (((x) & (V_POSTION_MASK)) >> (V_POSITION))
#define GET_N(x)            (((x) & (N_POSTION_MASK)) >> (N_POSITION))
#define GET_C(x)            (((x) & (C_POSTION_MASK)) >> (C_POSITION))

#define BVNC_PACK(B,V,N,C)  ((((IMG_UINT64)B)) << (B_POSITION) | \
                             (((IMG_UINT64)V)) << (V_POSITION) | \
                             (((IMG_UINT64)N)) << (N_POSITION) | \
                             (((IMG_UINT64)C)) << (C_POSITION) \
                            )

#define RGX_CR_CORE_ID_CONFIG_N_SHIFT    (8U)
#define RGX_CR_CORE_ID_CONFIG_C_SHIFT    (0U)

#define RGX_CR_CORE_ID_CONFIG_N_CLRMSK   (0XFFFF00FFU)
#define RGX_CR_CORE_ID_CONFIG_C_CLRMSK   (0XFFFFFF00U)

/* The default number of OSID is 1, higher number implies VZ enabled firmware */
#if !defined(RGXFW_NATIVE) && defined(PVRSRV_VZ_NUM_OSID) && (PVRSRV_VZ_NUM_OSID + 1U > 1U)
#define RGXFW_NUM_OS PVRSRV_VZ_NUM_OSID
#else
#define RGXFW_NUM_OS 1U
#endif

#define RGXFW_MAX_NUM_OS                                  (8U)
#define RGXFW_HOST_OS                                     (0U)
#define RGXFW_GUEST_OSID_START                            (1U)

#define RGXFW_THREAD_0                                    (0U)
#define RGXFW_THREAD_1                                    (1U)

/* META cores (required for the RGX_FEATURE_META) */
#define MTP218   (1)
#define MTP219   (2)
#define LTP218   (3)
#define LTP217   (4)

/* META Core memory feature depending on META variants */
#define RGX_META_COREMEM_32K      (32*1024)
#define RGX_META_COREMEM_48K      (48*1024)
#define RGX_META_COREMEM_64K      (64*1024)
#define RGX_META_COREMEM_96K      (96*1024)
#define RGX_META_COREMEM_128K     (128*1024)
#define RGX_META_COREMEM_256K     (256*1024)

#if !defined(SUPPORT_MULTIBVNC)
#if defined(SUPPORT_TRUSTED_DEVICE) && !defined(RGX_FEATURE_META_DMA)
#undef SUPPORT_META_COREMEM
#undef RGX_FEATURE_META_COREMEM_SIZE
#define RGX_FEATURE_META_COREMEM_SIZE (0)
#define RGX_META_COREMEM_SIZE         (0)
#else
#define RGX_META_COREMEM_SIZE         (RGX_FEATURE_META_COREMEM_SIZE*1024U)
#endif

#if defined(RGX_FEATURE_META_COREMEM_SIZE) && RGX_FEATURE_META_COREMEM_SIZE != 0
#define RGX_META_COREMEM          (1)
#define RGX_META_COREMEM_CODE     (1)
#define RGX_META_COREMEM_DATA     (1)
#endif
#endif

#define GET_ROGUE_CACHE_LINE_SIZE(x)    ((((IMG_INT32)x) > 0) ? ((x)/8) : (0))


#define MAX_HW_TA3DCONTEXTS	2U

#define RGX_CR_CLK_CTRL0_ALL_ON   (IMG_UINT64_C(0x5555555555555555)&RGX_CR_CLK_CTRL0_MASKFULL)
#define RGX_CR_CLK_CTRL0_ALL_AUTO (IMG_UINT64_C(0xaaaaaaaaaaaaaaaa)&RGX_CR_CLK_CTRL0_MASKFULL)
#define RGX_CR_CLK_CTRL1_ALL_ON   (IMG_UINT64_C(0x5555555555555555)&RGX_CR_CLK_CTRL1_MASKFULL)
#define RGX_CR_CLK_CTRL1_ALL_AUTO (IMG_UINT64_C(0xaaaaaaaaaaaaaaaa)&RGX_CR_CLK_CTRL1_MASKFULL)
#define RGX_CR_CLK_CTRL2_ALL_ON   (IMG_UINT64_C(0x5555555555555555)&RGX_CR_CLK_CTRL2_MASKFULL)
#define RGX_CR_CLK_CTRL2_ALL_AUTO (IMG_UINT64_C(0xaaaaaaaaaaaaaaaa)&RGX_CR_CLK_CTRL2_MASKFULL)

#define RGX_CR_MERCER0_SOFT_RESET_SPU_EN (RGX_CR_MERCER_SOFT_RESET_SPU0_MERCER0_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU1_MERCER0_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU2_MERCER0_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU3_MERCER0_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU4_MERCER0_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU5_MERCER0_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU6_MERCER0_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU7_MERCER0_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU8_MERCER0_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU9_MERCER0_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU10_MERCER0_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU11_MERCER0_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU12_MERCER0_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU13_MERCER0_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU14_MERCER0_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU15_MERCER0_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU16_MERCER0_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU17_MERCER0_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU18_MERCER0_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU19_MERCER0_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU20_MERCER0_EN)

#define RGX_CR_MERCER1_SOFT_RESET_SPU_EN (RGX_CR_MERCER_SOFT_RESET_SPU0_MERCER1_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU1_MERCER1_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU2_MERCER1_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU3_MERCER1_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU4_MERCER1_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU5_MERCER1_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU6_MERCER1_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU7_MERCER1_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU8_MERCER1_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU9_MERCER1_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU10_MERCER1_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU11_MERCER1_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU12_MERCER1_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU13_MERCER1_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU14_MERCER1_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU15_MERCER1_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU16_MERCER1_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU17_MERCER1_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU18_MERCER1_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU19_MERCER1_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU20_MERCER1_EN)

#define RGX_CR_MERCER2_SOFT_RESET_SPU_EN (RGX_CR_MERCER_SOFT_RESET_SPU0_MERCER2_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU1_MERCER2_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU2_MERCER2_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU3_MERCER2_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU4_MERCER2_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU5_MERCER2_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU6_MERCER2_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU7_MERCER2_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU8_MERCER2_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU9_MERCER2_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU10_MERCER2_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU11_MERCER2_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU12_MERCER2_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU13_MERCER2_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU14_MERCER2_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU15_MERCER2_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU16_MERCER2_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU17_MERCER2_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU18_MERCER2_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU19_MERCER2_EN | \
										  RGX_CR_MERCER_SOFT_RESET_SPU20_MERCER2_EN)


/* SOFT_RESET steps as defined in the TRM */
#define RGX_SOFT_RESET_JONES             (RGX_CR_SOFT_RESET_PM_EN | \
                                          RGX_CR_SOFT_RESET_ISP_EN)
#define RGX_SOFT_RESET_JONES_ALL         (RGX_SOFT_RESET_JONES | \
                                          RGX_CR_SOFT_RESET_GARTEN_EN)
#define RGX_SOFT_RESET_EXTRA             (RGX_CR_SOFT_RESET_PIXEL_EN | \
                                          RGX_CR_SOFT_RESET_VERTEX_EN |  \
                                          RGX_CR_SOFT_RESET_GEO_VERTEX_EN | \
                                          RGX_CR_SOFT_RESET_GEO_SHARED_EN | \
                                          RGX_CR_SOFT_RESET_COMPUTE_EN | \
                                          RGX_CR_SOFT_RESET_TDM_EN)
#define RGX_SOFT_RESET_FROM_WITHIN_CORE  (RGX_CR_SOFT_RESET_MASKFULL ^ \
                                          (RGX_CR_SOFT_RESET_GARTEN_EN | \
                                           RGX_CR_SOFT_RESET_BIF_JONES_EN | \
                                           RGX_CR_SOFT_RESET_SLC_EN))


#define RGX_BIF_PM_PHYSICAL_PAGE_ALIGNSHIFT		(12U)
#define RGX_BIF_PM_PHYSICAL_PAGE_SIZE			(1U << RGX_BIF_PM_PHYSICAL_PAGE_ALIGNSHIFT)

#define RGX_BIF_PM_VIRTUAL_PAGE_ALIGNSHIFT		(14U)
#define RGX_BIF_PM_VIRTUAL_PAGE_SIZE			(1U << RGX_BIF_PM_VIRTUAL_PAGE_ALIGNSHIFT)

#define RGX_BIF_PM_FREELIST_BASE_ADDR_ALIGNSIZE	(32U)

/* To get the number of required Bernado/Phantom(s), divide
 * the number of clusters by 4 and round up
 */
#define RGX_REQ_NUM_PHANTOMS(CLUSTERS) ((CLUSTERS + 3U) / 4U)
#define RGX_REQ_NUM_BERNADOS(CLUSTERS) ((CLUSTERS + 3U) / 4U)
#define RGX_REQ_NUM_BLACKPEARLS(CLUSTERS) ((CLUSTERS + 3U) / 4U)

#if !defined(SUPPORT_MULTIBVNC)
# define RGX_NUM_PHANTOMS (RGX_REQ_NUM_PHANTOMS(RGX_FEATURE_NUM_CLUSTERS))
#endif

/*
 * META second thread feature depending on META variants and
 * available CoreMem
 */
#if defined(RGX_FEATURE_META) && (RGX_FEATURE_META == MTP218 || RGX_FEATURE_META == MTP219) && (RGX_FEATURE_META_COREMEM_SIZE >= 96)
#define RGXFW_META_SUPPORT_2ND_THREAD
#endif

/* NOTE: The firmware heap bases and sizes are defined here to simplify
 * #include dependencies, see rgxheapconfig.h for the full RGX virtual
 * address space layout. The maximum configurable size via RGX_FW_HEAP_SHIFT
 * is 32MiB (1<<25) and the minimum is 4MiB (1<<22); the default firmware
 * heap size is set to maximum 32MiB.
 *
 * The config heap takes up the last 64 KBytes from the total firmware heap
 * space. It is intended to act as a storage space for the kernel and
 * firmware CCB offset storage. The Main Firmware heap size is reduced
 * accordingly but most of the map / unmap functions must take into
 * consideration the entire range (i.e. main and config heap).
 */
#define RGX_FIRMWARE_NUMBER_OF_FW_HEAPS				(2)
#define RGX_FIRMWARE_HEAP_SHIFT						RGX_FW_HEAP_SHIFT
#define RGX_FIRMWARE_RAW_HEAP_BASE					(0xE1C0000000ULL)
#define RGX_FIRMWARE_RAW_HEAP_SIZE					(1U << RGX_FIRMWARE_HEAP_SHIFT)
#define RGX_FIRMWARE_CONFIG_HEAP_SIZE				(0x10000U)
#define RGX_FIRMWARE_MAIN_HEAP_SIZE					(RGX_FIRMWARE_RAW_HEAP_SIZE - RGX_FIRMWARE_CONFIG_HEAP_SIZE)

/* Host sub-heap order: MAIN + CONFIG */
#define RGX_FIRMWARE_HOST_MAIN_HEAP_BASE			RGX_FIRMWARE_RAW_HEAP_BASE
#define RGX_FIRMWARE_HOST_CONFIG_HEAP_BASE			(RGX_FIRMWARE_HOST_MAIN_HEAP_BASE + RGX_FIRMWARE_MAIN_HEAP_SIZE)

/* Guest sub-heap order: CONFIG + MAIN */
#define RGX_FIRMWARE_GUEST_CONFIG_HEAP_BASE			RGX_FIRMWARE_RAW_HEAP_BASE
#define RGX_FIRMWARE_GUEST_MAIN_HEAP_BASE			(RGX_FIRMWARE_GUEST_CONFIG_HEAP_BASE + RGX_FIRMWARE_CONFIG_HEAP_SIZE)

/*
 * The maximum configurable size via RGX_FW_HEAP_SHIFT is 32MiB (1<<25) and
 * the minimum is 4MiB (1<<22); the default firmware heap size is set to
 * maximum 32MiB.
 */
#if defined(RGX_FW_HEAP_SHIFT) && (RGX_FW_HEAP_SHIFT < 22 || RGX_FW_HEAP_SHIFT > 25)
#error "RGX_FW_HEAP_SHIFT is outside valid range [22, 25]"
#endif

/*
 * FBC clear color register defaults based on HW defaults
 * non-YUV clear colour 0: 0x00000000 (encoded as ch3,2,1,0)
 * non-YUV clear colour 1: 0x01000000 (encoded as ch3,2,1,0)
 * YUV clear colour 0: 0x000 000 (encoded as UV Y)
 * YUV clear colour 1: 0x000 3FF (encoded as UV Y)
 */
#define RGX_FBC_CC_DEFAULT (0x0100000000000000)
#define RGX_FBC_CC_YUV_DEFAULT (0x000003FF00000000)

/*
 * Virtualisation definitions
 */

#define RGX_VIRTUALISATION_REG_SIZE_PER_OS (RGX_CR_MTS_SCHEDULE1 - RGX_CR_MTS_SCHEDULE)


/* GPU CR timer tick in GPU cycles */
#define RGX_CRTIME_TICK_IN_CYCLES (256U)

/*
 * Register used by the FW to track the current boot stage (not used in MIPS)
 */
#define RGX_FW_BOOT_STAGE_REGISTER     (RGX_CR_SCRATCH14)

/*
 * Define used to determine whether or not SLC range-based flush/invalidate
 * interface is supported.
 */
#define RGX_SRV_SLC_RANGEBASED_CFI_SUPPORTED 1

#endif /* RGXDEFS_KM_H */
