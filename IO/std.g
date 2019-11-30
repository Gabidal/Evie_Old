#_NULL_ is always uninitialized
var _NULL_
#true == 1
var true
#false == 0
var false

func init_std()
(
  #init std variables
  true = 1
  false = 0
)

type raw_vector
(
	var size
	var value
	var previus
	var next
)

func vector(v, val)
(
	v : 0 = 4
	v : 4 = val

	new raw_vector p
	v : 8 = p

	new raw_vector n
	v : 12 = n
)