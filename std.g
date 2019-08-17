var return = 0
var header = 0
var carry = 0
var true = 1
var false = 0

func gout name size 
  sys 4 1 name size 80h carry 
ret 

func gin name size 
  sys 3 2 name size 80h carry 
ret 

func file.open name 
  sys 5 name 0 0777 80h header 
ret 

func file.make name 
  sys 8 name 0777 0 80h header 
ret 

func file.close 
  sys 6 header 0 0 80h header
ret

func file.write text size 
  sys 4 1 text size 80h carry 
ret 

func file.read name size 
  sys 3 header name size 80h carry 
ret 

type vector 
  var i = 0 
  var init : 256 
  func push name index value 
    name : index = value 
    index = index + true 
  ret 
; 

