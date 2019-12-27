func Feed_Foward(N, W, s)
(
	var current = 0
	var next = 1
	var tmp
	while (current <= s)
	(
		N:next = N:current * W:current
		current = next
		next = next + 1
	)
	return N
)

Feed_Foward()