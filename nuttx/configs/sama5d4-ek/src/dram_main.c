/*****************************************************************************
 * configs/sama5d4-ek/src/dram_main.c
 *
 *   Copyright (C) 2014 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdio.h>
#include <debug.h>

#include <arch/irq.h>
#include <apps/hex2bin.h>

#include "up_arch.h"
#include "mmu.h"
#include "cache.h"

#include "sama5d4-ek.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define DRAM_ENTRY       ((dram_entry_t)SAM_DDRCS_VSECTION)

#define DRAM_WAIT        1
#define DRAM_NOWAIT      0

#ifdef CONFIG_SAMA5D4EK_DRAM_START
#  define DRAM_BOOT_MODE DRAM_NOWAIT
#else
#  define DRAM_BOOT_MODE DRAM_WAIT
#endif

/****************************************************************************
 * Private Types
 ****************************************************************************/

typedef void (*dram_entry_t)(void);

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: dram_main
 *
 * Description:
 *   dram_main is a tiny program that runs in ISRAM.  dram_main will
 *   configure DRAM, present a prompt, load and Intel HEX file into DRAM,
 *   and either start that program or wait for you to break in with the
 *   debugger.
 *
 ****************************************************************************/

int dram_main(int argc, char *argv)
{
  int ret;

  /* Here we have a in memory value we can change in the debugger
   * to begin booting in NOR Flash
   */

  static volatile uint32_t wait = DRAM_BOOT_MODE;

  /* DRAM was already initialized at boot time, so we are ready to load the
   * Intel HEX stream into DRAM.
   */

  printf("Send Intel HEX file now\n");
  fflush(stdout);

  ret = hex2mem(0,                           /* Accept Intel HEX on stdin */
                (uint32_t)SAM_DDRCS_VSECTION,
                (uint32_t)(SAM_DDRCS_VSECTION + CONFIG_SAMA5_DDRCS_SIZE),
                0);
  if (ret < 0)
    {
      /* We failed the load */

      printf("ERROR: Intel HEX file load failed: %d\n", ret);
      fflush(stdout);
      for(;;);
    }

  /* No success indication.. The following cache/MMu operations will clobber
   * any I/O that we attempt (Hmm.. unless, perhaps, if we delayed.  But who
   * wants a delay?).
   */

  /* Interrupts must be disabled through the following.  In this configuration,
   * there should only be timer interrupts.  Your NuttX configuration must use
   * CONFIG_SERIAL_LOWCONSOLE=y or printf() will hang when the interrupts
   * are disabled!
   */

  (void)irqsave();

  /* Disable the caches and the MMU.  Disabling the MMU should be safe here
   * because there is a 1-to-1 identity mapping between the physical and
   * virtual addressing.
   */

  cp15_disable_mmu();
  cp15_disable_caches();

  /* Invalidate caches and TLBs */

  cp15_invalidate_icache();
  cp15_invalidate_dcache_all();
  cp15_invalidate_tlbs();

  /* Then jump into NOR flash */

  while (wait)
    {
    }

  DRAM_ENTRY();

  return 0; /* We should not get here in either case */
}