from RunProgram import RunProgram
from Memory import Memory 


m = Memory() 
rp = RunProgram( "300R", m )

for i in rp.opcodes:
    fn = rp.opcodes[ i ]
    rp.code = i
    fn()
    rp.PrintPC += 1
