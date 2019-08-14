use std.g
var x = 1
var y = 5
var z = 10
var one = 1
str fileName : 128
str buffer : 256

func main 
  gin %fileName %fileName.size 
  file.open %fileName 
  file.read %buffer %buffer.size 
  file.close 
  gout %buffer %buffer.size 
ret  
