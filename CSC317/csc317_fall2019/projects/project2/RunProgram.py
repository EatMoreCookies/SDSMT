

class RunProgram:
    def __init__( self, userInput, memory ):
        index = userInput.find( 'R' )
        address = userInput[0:index]
        self.memory = memory 

        # Create a dictionary to have the opcodes and calls to their instructions
        self.opcodes = { 0x0a: self.doASLOpA, 0x0: self.doBRKOpI, 
                    0x18: self.doCLCOpI, 0xd8: self.doCLDOpI, 
                    0x58: self.doCLIOpI, 0xB8: self.doCLVOpI, 
                    0xca:  self.doDEXOpI, 0x88: self.doDEYOpI, 
                    0xE8: self.doINXOpI, 0xc8: self.doINYOpI, 
                    0x4A: self.doLSROpA, 0xEA: self.doNOPOpI, 
                    0x48: self.doPHAOpI, 0x8: self.doPHPOpI, 
                    0x68: self.doPLAOpI, 0x28: self.doPLPOpI, 
                    0x2A: self.doROLOpA, 0x6A: self.doROROpA, 
                    0x38: self.doSECOpI, 0xF8: self.doSEDOpI, 
                    0x78: self.doSEIOpI, 0xAA: self.doTAXOpI, 
                    0xa8: self.doTAYOpI, 0xBA: self.doTSXOpI, 
                    0x8A: self.doTXAOpI, 0x9A: self.doTXSOpI, 0x98: self.doTYAOpI  }
        
        self.PC = int( address, 16 )
        self.AC = 0
        self.XR = 0
        self.YR = 0
        self.SR = 0
        # The 5 bit we ignore, so we will permantelly set it.
        self.SR |= 32
        self.SP = 0xFF

        self.negative = 128
        self.overflow = 64
        self.Break = 16
        self.decimal = 8
        self.Interrupt = 4
        self.zero = 2
        self.carry = 1
        
        self.printHeader()
        self.operation( )

    # Reads in the opcode from the starting program address
    # calls the right operation.
    def operation( self ):
        
        code = 0x1

        while code != 0x0:
            code = self.memory.getData( hex( self.PC ) ) 

            try:
                functionCall = self.opcodes[code]
                functionCall()  
            except:
                self.printInstruction( "{:02x}".format( code ), "???", "????", "-- --" )

            self.PC += 1
        
    def printHeader( self ):
        print( " PC  OPC  INS   AMOD OPRND  AC XR YR SP NV-BDIZC")
        ########12345678901234567890123456789012345678901234567890     

    def printInstruction( self, OPC, INS, AMOD, OPRND ):
        print( "", "{:02x}".format( self.PC ),"", OPC, "", INS, " ", AMOD,  OPRND, "", "{:02x}".format( self.AC ), "{:02x}".format( self.XR ), 
         "{:02x}".format( self.YR ), "{:02x}".format( self.SP ), "{0:08b}".format( self.SR ) )

    def doASLOpA( self ):
        temp = ( self.AC & 128 ) >> 7
        self.AC <<= 1
        if temp:
            self.SR |= 1
        else:
            self.SR & ~(1)
        
        self.AC = self.doFlags( self.AC )
        self.printInstruction( "0A", "ASL", "   A", "-- --" )

    def doBRKOpI( self ):
        self.SR |= self.Interrupt
        self.SR |= self.Break
        self.memory.setData( hex( self.SP ), self.PC >> 8 )
        self.SP -= 1
        self.memory.setData( hex( self.SP ), self.PC & 255 )
        self.SP -= 1
        self.memory.setData( hex( self.SP ), self.SR )
        self.SP -= 1
        self.printInstruction( "00", "BRK", "impl", "-- --" )
    
    def doCLCOpI( self ):
        self.SR &= ~( self.carry )
        self.printInstruction( "18", "CLC", "impl", "-- --" )
    
    def doCLDOpI( self ):
        self.SR &= ~( self.decimal )
        self.printInstruction( "D8", "CLD", "impl", "-- --" )

    def doCLIOpI( self ):
        self.SR &= ~( self.Interrupt )
        self.printInstruction( "58", "CLI", "impl", "-- --" )
    
    def doCLVOpI( self ):
        self.SR &= ~( self.overflow )
        self.printInstruction( "B8", "CLV", "impl", "-- --" )
    
    def doDEXOpI( self ):
        self.XR -= 1
        self.XR = self.clearTopBits( self.XR )
        self.XR = self.doFlags( self.XR )
        self.printInstruction( "CA", "DEX", "impl", "-- --" )
        
    def doDEYOpI( self ):
        self.YR -= 1
        self.YR = self.clearTopBits( self.YR )
        self.YR = self.doFlags( self.YR )
        self.printInstruction( "88", "DEY", "impl", "-- --" )

    def doINXOpI( self ):
        self.XR += 1
        self.XR = self.clearTopBits( self.XR )
        self.XR = self.doFlags( self.XR )
        self.printInstruction( "E8", "INX", "impl", "-- --" )
    
    def doINYOpI( self ):
        self.YR += 1
        self.YR = self.clearTopBits( self.YR )
        self.YR = self.doFlags( self.YR )
        self.printInstruction( "C8", "INY", "impl", "-- --" )

    def doLSROpA( self ):
        temp = self.AC & 1 
        self.AC >>= 1
        # This sets the carry, since the carry is in bit 0 of the SR
        self.SR |= temp
        self.AC = self.doFlags( self.AC )
        self.printInstruction( "4A", "LSR", "   A", "-- --" )
    
    def doNOPOpI( self ):
        self.printInstruction( "EA", "NOP", "impl", "-- --" )
    
    def doPHAOpI( self ):
        self.memory.setData( hex( self.SP ), self.AC )
        self.SP -= 1
        self.printInstruction( "48", "PHA", "impl", "-- --" )
      
    def doPHPOpI( self ):
        self.memory.setData( hex( self.SP ), self.SR )
        self.SP -= 1 
        self.printInstruction( "08", "PHP", "impl", "-- --" )

    def doPLAOpI( self ):
        self.AC = self.memory.getData( hex( self.SP + 1 ) )
        self.SP += 1
        self.AC = self.doFlags( self.AC )
        self.printInstruction( "68", "PLA", "impl", "-- --" )
    
    def doPLPOpI( self ):
        self.SR = self.memory.getData( hex( self.SP + 1 ) )
        self.SP += 1
        self.printInstruction( "28", "PLP", "impl", "-- --" )
        
    def doROLOpA( self ):
        temp = ( 128 & self.AC ) >> 7
        self.AC <<= 1
        self.AC |= ( self.SR & self.carry )
        # This sets the carry, since the carry is in bit 0 of the SR
        if temp:
            self.SR |= 1
        else:
            self.SR &= 254 
        self.AC = self.doFlags( self.AC )
        self.printInstruction( "2A", "ROL", "   A", "-- --" )
    
    def doROROpA( self ):
        temp = 1 & self.AC
        self.AC >>= 1
        self.AC |= ( self.SR & self.carry ) << 7
        # This sets the carry, since the carry is in bit 0 of the SR
        if temp:
            self.SR |= 1
        else:
            self.SR &= 254
        self.AC = self.doFlags( self.AC )
        self.printInstruction( "6A", "ROR", "   A", "-- --" )
    
    def doSECOpI( self ): 
       self.SR |= self.carry
       self.printInstruction( "38", "SEC", "impl", "-- --" )
    
    def doSEDOpI( self ):
        self.SR |= self.decimal
        self.printInstruction( "F8", "SED", "impl", "-- --" )

    def doSEIOpI( self ):
        self.SR |= self.Interrupt
        self.printInstruction( "78", "SEI", "impl", "-- --" )
    
    def doTAXOpI( self ):
        self.XR = self.AC
        self.XR = self.doFlags( self.XR )
        self.printInstruction( "AA", "TAX", "impl", "-- --" )

    def doTAYOpI( self ):
        self.YR = self.AC
        self.YR = self.doFlags( self.YR )
        self.printInstruction( "A8", "TAY", "impl", "-- --" )
            
    def doTSXOpI( self ):
        self.XR = self.SP
        self.XR = self.doFlags( self.XR )
        self.printInstruction( "BA", "TSX", "impl", "-- --" ) 
    
    def doTXAOpI( self ):
        self.AC = self.XR
        self.AC = self.doFlags( self.AC )
        self.printInstruction( "8A", "TXA", "impl", "-- --" )
    
    def doTXSOpI( self ):
        self.SP = self.XR
        self.printInstruction( "9A", "TXS", "impl", "-- --" )
        
    def doTYAOpI( self ):
        self.AC = self.YR
        self.AC = self.doFlags( self.AC )
        self.printInstruction( "98", "TYA", "impl", "-- --" )
    
    def doFlags( self, register ):
        if register == 0:
            self.SR |= self.zero

        if self.isNegative( register ):
            self.SR |= self.negative
        
        register = self.clearTopBits( register )       
        return register 
                
    def isNegative( self, register ):
        if 128 & register:
            return True
        else:
            return False
    
    def clearTopBits( self, register ):
         register &= 255
         return register



            
    
    

    
