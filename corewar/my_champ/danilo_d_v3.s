.name "SvinyA"
.comment "Hey Kappa Kappa Hey"
.extend

l2:	sti	r1,%:live,%1
	and	r1,%0,r1
	fork	%:live
	fork	%:miss
	fork	%:base
	ld	%1, r7
	ld	%1, r8
	fork	%:kappa
	zjmp	%4000
live:	live	%1
	zjmp	%:live

base:	st	r1,5
	live	%1
	ld	%40, r2
	add	r2, r3, r3
	sti	r1, r3, r2
	zjmp	%:base

miss:	ld	%10,r6
	add	r6, r6, r6
	sti	r1, r1, r6
	zjmp	%:miss

kappa:	add	r8, r7, r7
	add	r8, r7, r8
	sti	r1, r7, %1
	sti	r1, r8, %1
	zjmp	%:kappa
