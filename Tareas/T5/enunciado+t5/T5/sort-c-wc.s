	.file	"sort-c-wc.c"
	.option nopic
	.attribute arch, "rv32i2p0_m2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	countWords
	.type	countWords, @function
countWords:
	mv	a5,a0
	lbu	a4,0(a0)
	beq	a4,zero,.L5
	li	a3,0
	li	a0,0
	li	a2,32
	li	a1,0
	li	a6,1
	j	.L4
.L6:
	mv	a3,a1
.L3:
	addi	a5,a5,1
	lbu	a4,0(a5)
	beq	a4,zero,.L8
.L4:
	beq	a4,a2,.L6
	bne	a3,zero,.L3
	addi	a0,a0,1
	mv	a3,a6
	j	.L3
.L8:
	ret
.L5:
	li	a0,0
	ret
	.size	countWords, .-countWords
	.align	2
	.globl	strCmp
	.type	strCmp, @function
strCmp:
	lbu	a5,0(a0)
	beq	a5,zero,.L16
	li	a6,0
	li	a4,0
	li	a3,32
	li	a2,0
	li	a7,1
	j	.L12
.L17:
	mv	a4,a2
.L11:
	addi	a0,a0,1
	lbu	a5,0(a0)
	beq	a5,zero,.L10
.L12:
	beq	a5,a3,.L17
	bne	a4,zero,.L11
	addi	a6,a6,1
	mv	a4,a7
	j	.L11
.L16:
	li	a6,0
.L10:
	lbu	a5,0(a1)
	beq	a5,zero,.L18
	li	a2,0
	li	a4,0
	li	a3,32
	li	a0,0
	li	a7,1
	j	.L15
.L19:
	mv	a4,a0
.L14:
	addi	a1,a1,1
	lbu	a5,0(a1)
	beq	a5,zero,.L13
.L15:
	beq	a5,a3,.L19
	bne	a4,zero,.L14
	addi	a2,a2,1
	mv	a4,a7
	j	.L14
.L18:
	li	a2,0
.L13:
	sub	a0,a6,a2
	ret
	.size	strCmp, .-strCmp
	.align	2
	.globl	sort
	.type	sort, @function
sort:
	addi	sp,sp,-32
	sw	ra,28(sp)
	sw	s0,24(sp)
	sw	s1,20(sp)
	sw	s2,16(sp)
	sw	s3,12(sp)
	sw	s4,8(sp)
	slli	s3,a1,2
	addi	s3,s3,-4
	add	s3,a0,s3
	bgeu	a0,s3,.L22
	mv	s4,a0
	mv	s0,a0
	j	.L26
.L24:
	sw	s2,0(s0)
	sw	s1,4(s0)
	mv	s0,s4
.L26:
	lw	s1,0(s0)
	lw	s2,4(s0)
	mv	a1,s2
	mv	a0,s1
	call	strCmp
	bgt	a0,zero,.L24
	addi	s0,s0,4
	bgtu	s3,s0,.L26
.L22:
	lw	ra,28(sp)
	lw	s0,24(sp)
	lw	s1,20(sp)
	lw	s2,16(sp)
	lw	s3,12(sp)
	lw	s4,8(sp)
	addi	sp,sp,32
	jr	ra
	.size	sort, .-sort
	.ident	"GCC: (GNU) 11.1.0"
