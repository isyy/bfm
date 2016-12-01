## #0669 is an interpretor for #0669 code. it does not allow for indents or spacing and properly handles an EOF, given you appent ! at the exit situation. ##
openfile = raw_input("brain**** file to open: ")
eof = 0
file = open(openfile, 'r')

s = "stack()"

## start parsing, char by char. ##
while (exit == 0):
  while True:
    
    ch == f.read(1)
    
    ## init the "stack" ##
    stack = []
    ## command parsing ##
    if (ch == !):
      exit == 1
      break
    if (c == +):
      
