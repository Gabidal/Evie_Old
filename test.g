use std.g
var x = 1
var y = 5
var z = 10
var one = 1
var buffer : 256
str fileName = "nand.g"

func main 
  file.open fileName 
  file.read %buffer %buffer.size 
  file.close 
  gout %buffer %buffer.size 
ret  
