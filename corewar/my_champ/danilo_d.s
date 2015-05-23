.name "Sejuani"
.comment "Tonight we hunt"
.extend

l2:	sti	r1,%:live,%1
	and	r1,%0,r1
	fork	%:base
live:	live	%1
	zjmp	%:live

base:	st	r1,1
	live	%1
	ld	%40, r2
	add	r2, r3, r3
	sti	r1, r3, r2
	zjmp	%:base

.code 42 DE AD C0 DE 12 34 61 34 61 23 61
