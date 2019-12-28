func Feed_Foward(N, W, s)
(
	var current = 0
	var next = 1
	while (current <= s)
	(
		N:next = N:current * W:current
		current = next
		next = next + 1
	)
	return N
)

func main()
(
	var Nodes = malloc(100)
	var Weights = malloc(100)
	Feed_Foward(Nodes, Weights, 100)
	return Nodes
	return Weights
)

main()