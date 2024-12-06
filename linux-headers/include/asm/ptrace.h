/* SPDX-License-Identifier: GPL-2.0-only WITH Linux-syscall-note */
/*
 * Copyright (C) 2012 Regents of the University of California
 */

#ifndef _ASM_RISCV_PTRACE_H
#define _ASM_RISCV_PTRACE_H

#ifndef __ASSEMBLY__

#include <linux/types.h>

#define PTRACE_GETFDPIC		33

#define PTRACE_GETFDPIC_EXEC	0
#define PTRACE_GETFDPIC_INTERP	1

#if __riscv_xlen == 64
typedef __u64 xlen_t;
#elif __riscv_xlen == 32
typedef __u32 xlen_t;
#else
#error "Unexpected __riscv_xlen"
#endif

/*
 * User-mode register state for core dumps, ptrace, sigcontext
 *
 * This decouples struct pt_regs from the userspace ABI.
 * struct user_regs_struct must form a prefix of struct pt_regs.
 */
struct user_regs_struct {
	xlen_t pc;
	xlen_t ra;
	xlen_t sp;
	xlen_t gp;
	xlen_t tp;
	xlen_t t0;
	xlen_t t1;
	xlen_t t2;
	xlen_t s0;
	xlen_t s1;
	xlen_t a0;
	xlen_t a1;
	xlen_t a2;
	xlen_t a3;
	xlen_t a4;
	xlen_t a5;
	xlen_t a6;
	xlen_t a7;
	xlen_t s2;
	xlen_t s3;
	xlen_t s4;
	xlen_t s5;
	xlen_t s6;
	xlen_t s7;
	xlen_t s8;
	xlen_t s9;
	xlen_t s10;
	xlen_t s11;
	xlen_t t3;
	xlen_t t4;
	xlen_t t5;
	xlen_t t6;
};

struct __riscv_f_ext_state {
	__u32 f[32];
	__u32 fcsr;
};

struct __riscv_d_ext_state {
	__u64 f[32];
	__u32 fcsr;
};

struct __riscv_q_ext_state {
	__u64 f[64] __attribute__((aligned(16)));
	__u32 fcsr;
	/*
	 * Reserved for expansion of sigcontext structure.  Currently zeroed
	 * upon signal, and must be zero upon sigreturn.
	 */
	__u32 reserved[3];
};

struct __riscv_ctx_hdr {
	__u32 magic;
	__u32 size;
};

struct __riscv_extra_ext_header {
	__u32 __padding[129] __attribute__((aligned(16)));
	/*
	 * Reserved for expansion of sigcontext structure.  Currently zeroed
	 * upon signal, and must be zero upon sigreturn.
	 */
	__u32 reserved;
	struct __riscv_ctx_hdr hdr;
};

union __riscv_fp_state {
	struct __riscv_f_ext_state f;
	struct __riscv_d_ext_state d;
	struct __riscv_q_ext_state q;
};

struct __riscv_v_ext_state {
	unsigned long vstart;
	unsigned long vl;
	unsigned long vtype;
	unsigned long vcsr;
	unsigned long vlenb;
	void *datap;
	/*
	 * In signal handler, datap will be set a correct user stack offset
	 * and vector registers will be copied to the address of datap
	 * pointer.
	 */
};

struct __riscv_v_regset_state {
	unsigned long vstart;
	unsigned long vl;
	unsigned long vtype;
	unsigned long vcsr;
	unsigned long vlenb;
	char vreg[];
};

/*
 * According to spec: The number of bits in a single vector register,
 * VLEN >= ELEN, which must be a power of 2, and must be no greater than
 * 2^16 = 65536bits = 8192bytes
 */
#define RISCV_MAX_VLENB (8192)

#endif /* __ASSEMBLY__ */

#endif /* _ASM_RISCV_PTRACE_H */
