
class RunProgram:
    def __init__( self, userInput, memory ):
        index = userInput.find( 'R' )
        address = userInput[0:index]
        self.memory = memory 
        
        self.PC = address
        self.AC = 0
        self.Xr = 0
        self.Yr = 0
        self.SR = 0
        self.SP = 0