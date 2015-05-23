.name "Le CE"
.comment "just a basic CE"
.extend

l1:	sti	r1,%:live3,%1
	ld	%10,r2
	ld      %25,r3
	and	r1,%0,r1

live3:	live	%1
	fork	%:suite3
	zjmp	%:live3

suite3:	add	r2,r3,r3
	add	r2,r1,r2
	st	r1,1
	live	%1
	sti	r1,r2,r3
	sti	r2,r1,r3
	zjmp	%:suite3
