class RunProgram:
    def __init__( self, userInput, memory ):
        index = userInput.find( 'R' )
        address = userInput[0:index]
        self.memory = memory 

        # Create a dictionary to have the opcodes and calls to their instructions
        self.opcodes = { 
                    # Project 2
                    0x0a: self.doASLOpA, 0x0:  self.doBRKOpI, 
                    0x18: self.doCLCOpI, 0xd8: self.doCLDOpI, 
                    0x58: self.doCLIOpI, 0xB8: self.doCLVOpI, 
                    0xca: self.doDEXOpI, 0x88: self.doDEYOpI, 
                    0xE8: self.doINXOpI, 0xc8: self.doINYOpI, 
                    0x4A: self.doLSROpA, 0xEA: self.doNOPOpI, 
                    0x48: self.doPHAOpI, 0x8:  self.doPHPOpI, 
                    0x68: self.doPLAOpI, 0x28: self.doPLPOpI, 
                    0x2A: self.doROLOpA, 0x6A: self.doROROpA, 
                    0x38: self.doSECOpI, 0xF8: self.doSEDOpI, 
                    0x78: self.doSEIOpI, 0xAA: self.doTAXOpI, 
                    0xa8: self.doTAYOpI, 0xBA: self.doTSXOpI, 
                    0x8A: self.doTXAOpI, 0x9A: self.doTXSOpI, 
                    0x98: self.doTYAOpI, 0x60: self.doRTSOpI,
                    
                    # Immediate
                    0x69: self.doADCOpIm, 0x29: self.doANDOpIm,
                    0xC9: self.doCMPOpIm, 0xE0: self.doCPXOpIm, 
                    0xC0: self.doCPYOpIm, 0x49: self.doEOROpIm, 
                    0xA9: self.doLDAOpIm, 0xA2: self.doLDXOpIm, 
                    0xA0: self.doLDYOpIm, 0x09: self.doORAOpIm,
                    0xE9: self.doSBCOpIm,

                    # Zeropage
                    0x65: self.doADCOpZp,  0x84: self.doSTYOpZp,
                    0x06: self.doASLOpZp,  0x25: self.doANDOpZp, 
                    0xC5: self.doCMPOpZp,  0xE4: self.doCPXOpZp,
                    0xC4: self.doCPYOpZp,  0xC6: self.doDECOpZp,
                    0x45: self.doEOROpZp,  0xE6: self.doINCOpZp,
                    0xA5: self.doLDAOpZp,  0xA6: self.doLDXOpZp,
                    0xA4: self.doLDYOpZp,  0x46: self.doLSROpZp, 
                    0x05: self.doORAOpZp,  0x26: self.doROLOpZp,
                    0x66: self.doROROpZp,  0xE5: self.doSBCOpZp,
                    0x85: self.doSTAOpZp,  0x86: self.doSTXOpZp,
                    0x24: self.doBITOpZp,

                    # Absolute 
                    0x6D: self.doADCOpAb,  0x8C: self.doSTYOpAb,
                    0x0E: self.doASLOpAb,  0x2D: self.doANDOpAb, 
                    0xCD: self.doCMPOpAb,  0xEC: self.doCPXOpAb,
                    0xCC: self.doCPYOpAb,  0xCE: self.doDECOpAb,
                    0x4D: self.doEOROpAb,  0xEE: self.doINCOpAb,
                    0xAD: self.doLDAOpAb,  0xAE: self.doLDXOpAb,
                    0xAC: self.doLDYOpAb,  0x4E: self.doLSROpAb, 
                    0x0D: self.doORAOpAb,  0x2E: self.doROLOpAb,
                    0x6E: self.doROROpAb,  0xED: self.doSBCOpAb,
                    0x8D: self.doSTAOpAb,  0x8E: self.doSTXOpAb,
                    0x2C: self.doBITOpAb,  0x20: self.doJSROpAb,
                    0x4C: self.doJMPOpAb,
            
                    # Indirect
                    0x6C: self.doJMPOpIn,

                    # Relative
                    0x90: self.doBCCOpRe, 0xB0: self.doBCSOpRe,
                    0xF0: self.doBEQOpRe, 0x30: self.doBMIOpRe,
                    0xD0: self.doBNEOpRe, 0x10: self.doBPLOpRe,
                    0x50: self.doBVCOpRe, 0x70: self.doBVSOpRe,

                    # Indexed
                    0x75: self.indexedParser, 0x7D: self.indexedParser,
                    0x79: self.indexedParser, 0x61: self.indexedParser,
                    0x71: self.indexedParser, 0x35: self.indexedParser,
                    0x3D: self.indexedParser, 0x39: self.indexedParser,
                    0x21: self.indexedParser, 0x31: self.indexedParser,
                    0x16: self.indexedParser, 0x1E: self.indexedParser,
                    0xD5: self.indexedParser, 0xDD: self.indexedParser,
                    0xD9: self.indexedParser, 0xC1: self.indexedParser,
                    0xD1: self.indexedParser, 0xD6: self.indexedParser,
                    0xDE: self.indexedParser, 0x55: self.indexedParser,
                    0x5D: self.indexedParser, 0x59: self.indexedParser,
                    0x41: self.indexedParser, 0x51: self.indexedParser,
                    0xF6: self.indexedParser, 0xFE: self.indexedParser,
                    0xB5: self.indexedParser, 0xBD: self.indexedParser,
                    0xB9: self.indexedParser, 0xA1: self.indexedParser,
                    0xB1: self.indexedParser, 0xB6: self.indexedParser,
                    0xBE: self.indexedParser, 0xB4: self.indexedParser,
                    0xBC: self.indexedParser, 0x56: self.indexedParser,
                    0x5E: self.indexedParser, 0x15: self.indexedParser,
                    0x1D: self.indexedParser, 0x19: self.indexedParser,
                    0x01: self.indexedParser, 0x11: self.indexedParser,
                    0x36: self.indexedParser, 0x3E: self.indexedParser,
                    0x76: self.indexedParser, 0x7E: self.indexedParser,
                    0xF5: self.indexedParser, 0xFD: self.indexedParser,
                    0xF9: self.indexedParser, 0xE1: self.indexedParser,
                    0xF1: self.indexedParser, 0x95: self.indexedParser,
                    0x9D: self.indexedParser, 0x99: self.indexedParser,
                    0x81: self.indexedParser, 0x91: self.indexedParser,
                    0x96: self.indexedParser, 0x94: self.indexedParser
                }

        self.zeropageXOpcodes = { 0x75: self.doADCOpInx, 0x35: self.doANDOpInx,
                                  0x16: self.doASLOpInx, 0xD5: self.doCMPOpInx, 
                                  0xD6: self.doDECOpInx, 0x55: self.doEOROpInx,
                                  0xF6: self.doINCOpInx, 0xB5: self.doLDAOpInx,
                                  0xB4: self.doLDYOpInx, 0x56: self.doLSROpInx,
                                  0x15: self.doORAOpInx, 0x36: self.doROLOpInx,
                                  0x76: self.doROROpInx, 0xF5: self.doSBCOpInx,
                                  0x95: self.doSTAOpInx, 0x94: self.doSTYOpInx }
        
        self.zeropageYOpcodes = { 0xB6: self.doLDXOpInx, 0x96: self.doSTXOpInx }
        
        self.absoluteXOpcodes = { 0x7D: self.doADCOpInx, 0x3D: self.doANDOpInx, 
                                  0x1E: self.doASLOpInx, 0xDD: self.doCMPOpInx,
                                  0xDE: self.doDECOpInx, 0x5D: self.doEOROpInx, 
                                  0xFE: self.doINCOpInx, 0xBD: self.doLDAOpInx,
                                  0xBC: self.doLDYOpInx, 0x5E: self.doLSROpInx,
                                  0x1D: self.doORAOpInx, 0x3E: self.doROLOpInx, 
                                  0x7E: self.doROROpInx, 0xFD: self.doSBCOpInx,
                                  0x9D: self.doSTAOpInx }
        
        self.absoluteYOpcodes = { 0x79: self.doADCOpInx, 0x39:self.doANDOpInx, 
                                  0xD9: self.doCMPOpInx, 0x59: self.doEOROpInx, 
                                  0xB9: self.doLDAOpInx, 0xBE: self.doLDXOpInx,
                                  0x19: self.doORAOpInx, 0xF9: self.doSBCOpInx,
                                  0x99: self.doSTAOpInx }    
        
        self.indirectXOpcodes = { 0x61: self.doADCOpInx, 0x21: self.doANDOpInx,
                                  0xC1: self.doCMPOpInx, 0x41: self.doEOROpInx, 
                                  0xA1: self.doLDAOpInx, 0x01: self.doORAOpInx,
                                  0xE1: self.doSBCOpInx, 0x81: self.doSTAOpInx
                                }

        self.inderectYOpcodes = { 0x71:  self.doADCOpInx, 0x31: self.doANDOpInx,
                                  0xD1:  self.doCMPOpInx, 0x51: self.doEOROpInx,
                                  0xB1:  self.doLDAOpInx, 0x11: self.doORAOpInx, 
                                  0xF1:  self.doSBCOpInx, 0x91: self.doSTAOpInx                               
                                }

          
        self.PC = int( address, 16 )
        self.AC = 0
        self.XR = 0
        self.YR = 0
        self.SR = 0
        # The 5 bit we ignore, so we will permantelly set it.
        self.SR |= 32
        self.SP = 0x1FF

        self.code = 0x1

        self.PrintPC = self.PC

        self.negative = 128
        self.overflow = 64
        self.Break = 16
        self.decimal = 8
        self.Interrupt = 4
        self.zero = 2
        self.carry = 1

    # Reads in the opcode from the starting program address
    # calls the right operation.
    def operation( self ):
        self.printHeader( )

        while self.code != 0x0:
            self.code = self.memory.getData( hex( self.PC ) ) 

            self.PrintPC = self.PC

            try:
                functionCall = self.opcodes[self.code]
                functionCall()  
            except:
                self.printInstruction( "{:02x}".format( self.code ), "???", "????", "-- --" )

            self.PC += 1
        
    def printHeader( self ):
        print( " PC  OPC  INS    AMOD OPRND  AC XR YR SP NV-BDIZC")
          ########12345678901234567890123456789012345678901234567890     

    def printInstruction( self, OPC, INS, AMOD, OPRND ):
        if len( "{:02x}".format( self.PrintPC ) ) < 4:
            print( " ", end = '' )
        
        print( "{:02x}".format( self.PrintPC ),"", OPC, "", INS + "  " + AMOD,  OPRND, "", "{:02x}".format( self.AC ), "{:02x}".format( self.XR ), 
        "{:02x}".format( self.YR ), "{:02x}".format( self.SP & 255 ), "{0:08b}".format( self.SR ) )

    def doASLOpA( self ):
        self.AC = self.ASLOp( self.AC )
        self.printInstruction( "0A", "ASL", "     A", "-- --" )

    def doBRKOpI( self ):
        self.SR |= self.Interrupt
        self.SR |= self.Break
        self.memory.setData( hex( self.SP ), self.PC >> 8 )
        self.SP -= 1
        self.memory.setData( hex( self.SP ), self.PC & 255 )
        self.SP -= 1
        self.memory.setData( hex( self.SP ), self.SR )
        self.SP -= 1
        self.printInstruction( "00", "BRK", "  impl", "-- --" )
    
    def doCLCOpI( self ):
        self.SR &= ~( self.carry )
        self.printInstruction( "18", "CLC", "  impl", "-- --" )
    
    def doCLDOpI( self ):
        self.SR &= ~( self.decimal )
        self.printInstruction( "D8", "CLD", "  impl", "-- --" )

    def doCLIOpI( self ):
        self.SR &= ~( self.Interrupt )
        self.printInstruction( "58", "CLI", "  impl", "-- --" )
    
    def doCLVOpI( self ):
        self.SR &= ~( self.overflow )
        self.printInstruction( "B8", "CLV", "  impl", "-- --" )
    
    def doDEXOpI( self ):
        self.XR -= 1
        self.XR = self.clearTopBits( self.XR )
        self.XR = self.doFlags( self.XR )
        self.printInstruction( "CA", "DEX", "  impl", "-- --" )
        
    def doDEYOpI( self ):
        self.YR -= 1
        self.YR = self.clearTopBits( self.YR )
        self.YR = self.doFlags( self.YR )
        self.printInstruction( "88", "DEY", "  impl", "-- --" )

    def doINXOpI( self ):
        self.XR += 1
        self.XR = self.clearTopBits( self.XR )
        self.XR = self.doFlags( self.XR )
        self.printInstruction( "E8", "INX", "  impl", "-- --" )
    
    def doINYOpI( self ):
        self.YR += 1
        self.YR = self.clearTopBits( self.YR )
        self.YR = self.doFlags( self.YR )
        self.printInstruction( "C8", "INY", "  impl", "-- --" )

    def doLSROpA( self ):
        temp = self.AC & 1 
        self.AC >>= 1
          # This sets the carry, since the carry is in bit 0 of the SR
        self.SR |= temp
        self.AC = self.doFlags( self.AC )
        self.printInstruction( "4A", "LSR", "     A", "-- --" )
    
    def doNOPOpI( self ):
        self.printInstruction( "EA", "NOP", "  impl", "-- --" )
    
    def doPHAOpI( self ):
        self.memory.setData( hex( self.SP ), self.AC )
        self.SP -= 1
        self.printInstruction( "48", "PHA", "  impl", "-- --" )
      
    def doPHPOpI( self ):
        self.memory.setData( hex( self.SP ), self.SR )
        self.SP -= 1 
        self.printInstruction( "08", "PHP", "  impl", "-- --" )

    def doPLAOpI( self ):
        self.AC = self.memory.getData( hex( self.SP + 1 ) )
        self.SP += 1
        self.AC = self.doFlags( self.AC )
        self.printInstruction( "68", "PLA", "  impl", "-- --" )
    
    def doPLPOpI( self ):
        self.SR = self.memory.getData( hex( self.SP + 1 ) )
        self.SP += 1
        self.printInstruction( "28", "PLP", "  impl", "-- --" )
        
    def doROLOpA( self ):
        self.AC = self.ROLOp( self.AC )
        self.printInstruction( "2A", "ROL", "     A", "-- --" )
    
    def doROROpA( self ):
        self.AC = self.ROROp( self.AC )
        self.printInstruction( "6A", "ROR", "     A", "-- --" )
    
    def doSECOpI( self ): 
       self.SR |= self.carry
       self.printInstruction( "38", "SEC", "  impl", "-- --" )
    
    def doSEDOpI( self ):
        self.SR |= self.decimal
        self.printInstruction( "F8", "SED", "  impl", "-- --" )

    def doSEIOpI( self ):
        self.SR |= self.Interrupt
        self.printInstruction( "78", "SEI", "  impl", "-- --" )
    
    def doTAXOpI( self ):
        self.XR = self.AC
        self.XR = self.doFlags( self.XR )
        self.printInstruction( "AA", "TAX", "  impl", "-- --" )

    def doTAYOpI( self ):
        self.YR = self.AC
        self.YR = self.doFlags( self.YR )
        self.printInstruction( "A8", "TAY", "  impl", "-- --" )
            
    def doTSXOpI( self ):
        self.XR = self.SP
        self.XR = self.doFlags( self.XR )
        self.printInstruction( "BA", "TSX", "  impl", "-- --" ) 
    
    def doTXAOpI( self ):
        self.AC = self.XR
        self.AC = self.doFlags( self.AC )
        self.printInstruction( "8A", "TXA", "  impl", "-- --" )
    
    def doTXSOpI( self ):
        self.SP = self.XR
        self.printInstruction( "9A", "TXS", "  impl", "-- --" )
        
    def doTYAOpI( self ):
        self.AC = self.YR
        self.AC = self.doFlags( self.AC )
        self.printInstruction( "98", "TYA", "  impl", "-- --" )

    def doRTSOpI( self ):
        self.SP += 1
        lowByte = self.memory.getData( hex( self.SP ) )
        self.SP += 1
        highByte = self.memory.getData( hex( self.SP ) )

        self.PC = lowByte
        self.PC |= ( highByte << 8 )

        self.printInstruction( "60", "RTS", "  impl", "-- --" )


    #################################
    ######### Immediate Ops  ########
    #################################
    
    def doADCOpIm( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        self.AC = self.ADDOp( self.AC, val, True )
        self.printInstruction( "69", "ADC", "     #", "{:02x}".format( val ) +" --" )

    def doANDOpIm( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        self.AC = self.ANDOp( self.AC, val )
        self.printInstruction( "29", "AND", "     #", "{:02x}".format( val ) + " --" )

    def doCMPOpIm( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        self.CMPOp( self.AC, val )
        self.printInstruction( "C9", "CMP", "     #", "{:02x}".format( val ) + " --" )
    
    def doCPXOpIm( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        self.CMPOp( self.XR, val )
        self.printInstruction( "E0", "CPX", "     #", "{:02x}".format( val ) + " --" )

    def doCPYOpIm( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        self.CMPOp( self.YR, val )
        self.printInstruction( "C0", "CPY", "     #", "{:02x}".format( val ) + " --" )

    def doEOROpIm( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        self.AC = self.EOROp( self.AC, val )
        self.printInstruction( "49", "EOR", "     #", "{:02x}".format( val ) + " --" )
    
    def doLDAOpIm( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        self.AC = val
        self.AC = self.doFlags( self.AC )
        self.printInstruction( "A9", "LDA", "     #", "{:02x}".format( val ) + " --" )
    
    def doLDXOpIm( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        self.XR = val
        self.XR = self.doFlags( self.XR )
        self.printInstruction( "A2", "LDX", "     #", "{:02x}".format( val ) + " --" )
    
    def doLDYOpIm( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        self.YR = val
        self.YR = self.doFlags( self.YR )
        self.printInstruction( "A0", "LDY", "     #", "{:02x}".format( val ) + " --" )
    
    def doORAOpIm( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        self.AC = self.OROp( self.AC, val )
        self.printInstruction( "09", "ORA", "     #", "{:02x}".format( val ) + " --" )

    def doSBCOpIm( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        self.AC = self.SUBOp( self.AC, val, True )
        self.printInstruction( "E9", "SBC", "     #", "{:02x}".format( val ) + " --" )

    ###############################
    ######### Zeropage Ops ########
    ###############################

    def doADCOpZp( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        valCopy = val
        val = self.memory.getData( hex( val ) )
        self.AC = self.ADDOp( self.AC, val, True )
        self.printInstruction( "65", "ADC", "   zpg", "{:02x}".format( valCopy ) +" --" )
            
    def doASLOpZp( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        valCopy = val
        val = self.memory.getData( hex( val ) )
        val = self.ASLOp( val )
        self.memory.setData( hex( valCopy ), val )
        self.printInstruction( "06", "ASL", "   zpg", "{:02x}".format( valCopy ) + " --" )

    def doANDOpZp( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        valCopy = val
        val = self.memory.getData( hex( val ) )
        self.AC = self.ANDOp( self.AC, val )
        self.printInstruction( "25", "AND", "   zpg", "{:02x}".format( valCopy ) + " --" )
       
    def doCMPOpZp( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        valCopy = val
        val = self.memory.getData( hex( val ) )
        self.CMPOp( self.AC, val )
        self.printInstruction( "C5", "CMP", "   zpg", "{:02x}".format( valCopy ) + " --" )
    
    def doCPXOpZp( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        valCopy = val
        val = self.memory.getData( hex( val ) )
        self.CMPOp( self.XR, val )
        self.printInstruction( "E4", "CPX", "   zpg", "{:02x}".format( valCopy ) + " --" )

    def doCPYOpZp( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        valCopy = val
        val = self.memory.getData( hex( val ) )
        self.CMPOp( self.YR, val )
        self.printInstruction( "C4", "CPY", "   zpg", "{:02x}".format( valCopy ) + " --" )
    
    def doDECOpZp( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        valCopy = val

        val = self.memory.getData( hex( val ) )
        val = self.SUBOp( val, 1, False )
        
        self.memory.setData( hex( valCopy ), val )
        self.printInstruction( "C6", "DEC", "   zpg", "{:02x}".format( valCopy ) + " --" )

    def doEOROpZp( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        valCopy = val
        val = self.memory.getData( hex( val ) )
        self.AC = self.EOROp( self.AC, val )
        self.printInstruction( "45", "EOR", "   zpg", "{:02x}".format( valCopy ) + " --" )

    def doINCOpZp( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        valCopy = val
        
        val = self.memory.getData( hex( val ) )
        val = self.ADDOp( val, 1, False )

        self.memory.setData( hex( valCopy ), val )
        self.printInstruction( "E6", "INC", "   zpg", "{:02x}".format( valCopy ) + " --" )
    
    def doLDAOpZp( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        valCopy = val
        val = self.memory.getData( hex( val ) )
        self.AC = val
        self.AC = self.doFlags( self.AC )
        self.printInstruction( "A5", "LDA", "   zpg", "{:02x}".format( valCopy ) + " --" )
    
    def doLDXOpZp( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        valCopy = val
        val = self.memory.getData( hex( val ) )
        self.XR = val
        self.XR = self.doFlags( self.XR )
        self.printInstruction( "A6", "LDX", "   zpg", "{:02x}".format( valCopy ) + " --" )
    
    def doLDYOpZp( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        valCopy = val
        val = self.memory.getData( hex( val ) )
        self.YR = val
        self.YR = self.doFlags( self.YR )
        self.printInstruction( "A4", "LDA", "   zpg", "{:02x}".format( valCopy ) + " --" )

    def doLSROpZp( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        valCopy = val
        val = self.memory.getData( hex( val ) ) 
        val = self.LSROp( val )
        self.memory.setData( hex( valCopy ), val )
        self.printInstruction( "46", "LSR", "   zpg", "{:02x}".format( valCopy ) + " --" )

    def doORAOpZp( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        valCopy = val
        val = self.memory.getData( hex( val ) ) 
        self.AC = self.OROp( self.AC, val )
        self.printInstruction( "05", "ORA", "   zpg", "{:02x}".format( valCopy ) + " --" )
    
    def doROLOpZp( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        valCopy = val
        val = self.memory.getData( hex( val ) ) 
        val = self.ROLOp( val )
        self.memory.setData( hex( valCopy ), val )
        self.printInstruction( "26", "ROL", "   zpg", "{:02x}".format( valCopy ) + " --" )
    
    def doROROpZp( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        valCopy = val
        val = self.memory.getData( hex( val ) ) 
        val = self.ROROp( val )
        self.memory.setData( hex( valCopy ), val )
        self.printInstruction( "66", "ROR", "   zpg", "{:02x}".format( valCopy ) + " --" )
    
    def doSBCOpZp( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        valCopy = val
        val = self.memory.getData( hex( val ) ) 
        self.AC = self.SUBOp( self.AC, val, True )
        self.printInstruction( "66", "ROR", "   zpg", "{:02x}".format( valCopy ) + " --" )

    def doSTAOpZp( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        self.memory.setData( hex( val ), self.AC )
        self.printInstruction( "85", "STA", "   zpg", "{:02x}".format( val ) + " --" )
    
    def doSTXOpZp( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        self.memory.setData( hex( val ), self.XR )
        self.printInstruction( "86", "STX", "   zpg", "{:02x}".format( val ) + " --" )

    def doSTYOpZp( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
        self.memory.setData( hex( val ), self.YR )
        self.printInstruction( "84", "STY", "   zpg", "{:02x}".format( val ) + " --" )
    
    def doBITOpZp( self ):
        self.PC += 1
        val = self.memory.getData( hex( self.PC ) )
 
        if val & self.negative:
            self.SR |= self.negative

        else:
            self.SR &= ~( self.negative ) 

        if val & self.overflow:
            self.SR |= self.overflow

        else:
            self.SR &= ~( self.overflow ) 
        
        if self.ANDOp( self.AC, val ) == 0:
            self.SR |= self.zero
        
        else:
            self.SR &= ~( self.zero )
        
        self.printInstruction( "24", "STY", "   zpg", "{:02x}".format( val ) + " --" )

    
    ##################################
    ######## Absolute Methods ########
    ##################################

    def doADCOpAb( self ):
        data = self.getAbsoluteValue()
        self.AC = self.ADDOp( self.AC, data[0], True )
        self.printInstruction( "6D", "ADC", "   abs", "{:02x}".format( data[1] ) + " {:02x}".format( data[2] ) )
            
    def doASLOpAb( self ):
        data = self.getAbsoluteValue( )
        val = self.ASLOp( data[0] )
        self.memory.setData( hex( data[3] ), val )
        self.printInstruction( "0E", "ASL", "   abs", "{:02x}".format( data[1] ) + " {:02x}".format( data[2] ) )

    def doANDOpAb( self ):
        data = self.getAbsoluteValue()
        self.AC = self.ANDOp( self.AC, data[0] )
        self.printInstruction( "2D", "AND", "   abs", "{:02x}".format( data[1] ) + " {:02x}".format( data[2] ) )
       
    def doCMPOpAb( self ):
        data = self.getAbsoluteValue()
        self.CMPOp( self.AC, data[0] )
        self.printInstruction( "CD", "CMP", "   abs", "{:02x}".format( data[1] ) + " {:02x}".format( data[2] ) )
    
    def doCPXOpAb( self ):
        data = self.getAbsoluteValue()
        self.CMPOp( self.XR, data[0] )
        self.printInstruction( "EC", "CPX", "   abs", "{:02x}".format( data[1] ) + " {:02x}".format( data[2] ) )
    
    def doCPYOpAb( self ):
        data = self.getAbsoluteValue()
        self.CMPOp( self.YR, data[0] )
        self.printInstruction( "CC", "CPY", "   abs", "{:02x}".format( data[1] ) + " {:02x}".format( data[2] ) )
    
    def doDECOpAb( self ):
        data = self.getAbsoluteValue()
        val = self.SUBOp( data[0], 1, False )
        self.memory.setData( hex( data[3] ), val )
        self.printInstruction( "CE", "DEC", "   abs", "{:02x}".format( data[1] ) + " {:02x}".format( data[2] ) )

    def doEOROpAb( self ):
        data = self.getAbsoluteValue()
        self.AC = self.EOROp( self.AC, data[0] )
        self.printInstruction( "4D", "EOR", "   abs", "{:02x}".format( data[1] ) + " {:02x}".format( data[2] ) )

    def doINCOpAb( self ):
        data = self.getAbsoluteValue()
        val = self.ADDOp( data[0], 1, False )
        self.memory.setData( hex( data[3] ), val )
        self.printInstruction( "EE", "INC", "   abs", "{:02x}".format( data[1] ) + " {:02x}".format( data[2] ) )
    
    def doLDAOpAb( self ):
        data = self.getAbsoluteValue()
        self.AC = data[0]
        self.AC = self.doFlags( self.AC )
        self.printInstruction( "AD", "LDA", "   abs", "{:02x}".format( data[1] ) + " {:02x}".format( data[2] ) )
    
    def doLDXOpAb( self ):
        data = self.getAbsoluteValue()
        self.XR = data[0]
        self.XR = self.doFlags( self.XR )
        self.printInstruction( "AE", "LDX", "   abs", "{:02x}".format( data[1] ) + " {:02x}".format( data[2] ) )
    
    def doLDYOpAb( self ):
        data = self.getAbsoluteValue()
        self.YR = data[0]
        self.YR = self.doFlags( self.YR )
        self.printInstruction( "AC", "LDY", "   abs", "{:02x}".format( data[1] ) + " {:02x}".format( data[2] ) )
    
    def doLSROpAb( self ):
        data = self.getAbsoluteValue()
        val = self.LSROp( data[0] )
        self.memory.setData( hex( data[3]), val )
        self.printInstruction( "4E", "LSR", "   abs", "{:02x}".format( data[1] ) + " {:02x}".format( data[2] ) )

    def doORAOpAb( self ):
        data = self.getAbsoluteValue()
        self.AC = self.OROp( self.AC, data[0] ) 
        self.printInstruction( "0D", "ORA", "   abs", "{:02x}".format( data[1] ) + " {:02x}".format( data[2] ) )
    
    def doROLOpAb( self ):
        data = self.getAbsoluteValue()
        val = self.ROLOp( data[0] )
        self.memory.setData( hex( data[3] ), val )
        self.printInstruction( "2E", "ROL", "   abs", "{:02x}".format( data[1] ) + " {:02x}".format( data[2] ) )
    
    def doROROpAb( self ):
        data = self.getAbsoluteValue()
        val = self.ROROp( data[0] )
        self.memory.setData( hex( data[3] ), val )
        self.printInstruction( "6E", "ROR", "   abs", "{:02x}".format( data[1] ) + " {:02x}".format( data[2] ) )
      
    def doSBCOpAb( self ):
        data = self.getAbsoluteValue()
        self.AC = self.SUBOp( self.AC, data[0], True )
        self.printInstruction( "ED", "SBC", "   abs", "{:02x}".format( data[1] ) + " {:02x}".format( data[2] ) )

    def doSTAOpAb( self ):
        data = self.getAbsoluteValue()
        self.memory.setData( hex( data[3] ), self.AC )
        self.printInstruction( "8D", "STA", "   abs", "{:02x}".format( data[1] ) + " {:02x}".format( data[2] ) )
    
    def doSTXOpAb( self ):
        data = self.getAbsoluteValue()
        self.memory.setData( hex( data[3] ), self.XR )
        self.printInstruction( "8E", "STX", "   abs", "{:02x}".format( data[1] ) + " {:02x}".format( data[2] ) )

    def doSTYOpAb( self ):
        data = self.getAbsoluteValue()
        self.memory.setData( hex( data[3] ), self.YR )
        self.printInstruction( "8C", "STY", "   abs", "{:02x}".format( data[1] ) + " {:02x}".format( data[2] ) )

    def doBITOpAb( self ):
        data = self.getAbsoluteValue()
        
        if data[0] & self.negative:
            self.SR |= self.negative

        else:
            self.SR &= ~( self.negative ) 

        if data[0] & self.overflow:
            self.SR |= self.overflow

        else:
            self.SR &= ~( self.overflow ) 
        
        if self.ANDOp( self.AC, data[0] ) == 0:
            self.SR |= self.zero
        
        else:
            self.SR &= ~( self.zero )

        self.printInstruction( "2C", "BIT", "   abs", "{:02x}".format( data[1] ) + " {:02x}".format( data[2] ) )
    
    def doJSROpAb( self ):
        data = self.getAbsoluteValue()
        self.memory.setData( hex( self.SP ), self.PC >> 8 )
        self.SP -= 1
        self.memory.setData( hex( self.SP ), self.PC & 255 )
        self.SP -= 1
        self.PC = data[2] << 8
        self.PC |= data[1]
        # Decrement the program counter by 1 because the next cycle will fix it.
        self.PC -= 1
        self.printInstruction( "20", "JSR", "   abs", "{:02x}".format( data[1] ) + " {:02x}".format( data[2] ) )
        
    
    def doJMPOpAb( self ):
        data = self.getAbsoluteValue()
        self.PC = data[1]
        self.PC |= ( data[2] << 8 )
        self.PC -= 1
        self.printInstruction( "4C", "JMP", "   abs", "{:02x}".format( data[1] ) + " {:02x}".format( data[2] ) )

      ###########################
      ######## Indirect #########
      ###########################
    
    def doJMPOpIn( self ):
        data = self.getAbsoluteValue()
        self.PC = self.memory.getData( hex( data[3] ) )
        self.PC |= ( self.memory.getData( hex( data[3] + 1 ) ) << 8  )
        self.PC -= 1
        self.printInstruction( "6C", "JMP", "   ind", "{:02x}".format( data[1] ) + " {:02x}".format( data[2] ) )


      ###########################
      ######## Relative #########
      ###########################
    def doBCCOpRe( self ):
        self.PC += 1
        offset = self.memory.getData( hex( self.PC ) )
        if self.SR & self.carry == 0:
            self.PC += self.doSignExtend( offset )

        self.printInstruction( "90", "BCC", "   rel", "{:02x}".format( offset ) + " --" )

    def doBCSOpRe( self ):
        self.PC += 1
        offset = self.memory.getData( hex( self.PC ) )
        if self.SR & self.carry:
            self.PC += self.doSignExtend( offset )

        self.printInstruction( "B0", "BCS", "   rel", "{:02x}".format( offset ) + " --" )

    def doBEQOpRe( self ):      
        self.PC += 1
        offset = self.memory.getData( hex( self.PC ) )
        if self.SR & self.zero:
            self.PC += self.doSignExtend( offset )
        
        self.printInstruction( "F0", "BEQ", "   rel", "{:02x}".format( offset ) + " --" )

    def doBMIOpRe( self ):
        self.PC += 1
        offset = self.memory.getData( hex( self.PC ) )
        if self.SR & self.negative:
            self.PC += self.doSignExtend( offset )
        
        self.printInstruction( "30", "BMI", "   rel", "{:02x}".format( offset ) + " --" )

    def doBNEOpRe( self ):
        self.PC += 1
        offset = self.memory.getData( hex( self.PC ) )
        if self.SR & self.zero == 0:
            self.PC += self.doSignExtend( offset )
        
        self.printInstruction( "D0", "BNE", "   rel", "{:02x}".format( offset ) + " --" )

    def doBPLOpRe( self ):
        self.PC += 1
        offset = self.memory.getData( hex( self.PC ) )
        if self.SR & self.negative == 0:
            self.PC += self.doSignExtend( offset )
        
        self.printInstruction( "10", "BLP", "   rel", "{:02x}".format( offset ) + " --" )

    def doBVCOpRe( self ):
        self.PC += 1
        offset = self.memory.getData( hex( self.PC ) )
        if self.SR & self.overflow == 0:
           self.PC += self.doSignExtend( offset )
        
        self.printInstruction( "50", "BVC", "   rel", "{:02x}".format( offset ) + " --" )

    def doBVSOpRe( self ):
        self.PC += 1
        offset = self.memory.getData( hex( self.PC ) )
        if self.SR & self.overflow:
            self.PC += self.doSignExtend( offset )
        
        self.printInstruction( "70", "BVS", "   rel", "{:02x}".format( offset ) + " --" )

    ##########################
    ######## Indexed #########
    ##########################
    def indexedParser( self ):
        address = int
        AMOD = str
        operands = []
        INS = str

        if self.checkDict( self.code, self.zeropageXOpcodes ):
            self.PC += 1
            operands.append( self.memory.getData( hex( self.PC ) ) )
            address = ( operands[0] + self.XR ) & 255
            operands[0] = ( "{:02x}".format( operands[0] ) )
            AMOD = " zpg,x"
            operands.append( " --" )
            indexCall = self.zeropageXOpcodes[ self.code ]
            INS = indexCall( address )


        elif self.checkDict( self.code, self.zeropageYOpcodes ):
            self.PC += 1
            operands.append( self.memory.getData( hex( self.PC ) ) )
            address = ( operands[0] + self.YR ) & 255
            operands[0] = ( "{:02x}".format( operands[0] ) )
            AMOD = " zpg,y"
            operands.append( " --" )
            indexCall = self.zeropageYOpcodes[ self.code ]
            INS = indexCall( address )
        
        elif self.checkDict( self.code, self.absoluteXOpcodes ):
            data = self.getAbsoluteValue( )
            address = data[3] + self.XR
            operands.append( "{:02x}".format( data[1] ) )
            operands.append( " {:02x}".format( data[2] ) )
            AMOD = " abs,x"
            indexCall = self.absoluteXOpcodes[ self.code ]
            INS = indexCall( address )

        elif self.checkDict( self.code, self.absoluteYOpcodes ):
            data = self.getAbsoluteValue( )
            address = data[3] + self.YR
            operands.append( "{:02x}".format( data[1] ) )
            operands.append( " {:02x}".format( data[2] ) )
            AMOD = " abs,y"
            indexCall = self.absoluteYOpcodes[ self.code ]
            INS = indexCall( address )
        
        elif self.checkDict( self.code, self.indirectXOpcodes ):
            self.PC += 1
            operands.append( self.memory.getData( hex( self.PC ) ) )
            operands.append( " --")
            jumpAdressLow = self.memory.getData( hex( operands[0] + self.XR ) )
            jumpAddressHigh = self.memory.getData( hex( operands[0] + self.XR + 1 ) )
            operands[0] = ( "{:02x}".format( operands[0] ) )
            addressFinal = jumpAddressHigh << 8
            addressFinal |= jumpAdressLow 
            AMOD = " x,ind"
            indexCall = self.indirectXOpcodes[ self.code ]
            INS = indexCall( addressFinal )
            
        elif self.checkDict( self.code, self.inderectYOpcodes ):
            self.PC += 1
            operands.append( self.memory.getData( hex( self.PC ) ) )
            operands.append( " --")
            jumpAdressLow = self.memory.getData( hex( operands[0] ) )
            jumpAddressHigh = self.memory.getData( hex( operands[0] + 1 ) )
            operands[0] = ( "{:02x}".format( operands[0] ) )
            addressFinal = jumpAddressHigh << 8
            addressFinal |= jumpAdressLow 
            addressFinal += self.YR
            AMOD = " ind,y"
            indexCall = self.inderectYOpcodes[ self.code ]
            INS = indexCall( addressFinal )


        self.printInstruction( "{:02x}".format( self.code ), INS, AMOD, operands[0] + operands[1] )

            
    def doADCOpInx( self, address ):
        data = self.memory.getData( hex( address ) )
        self.AC = self.ADDOp( self.AC, data, True )
        return "ADC"

    def doANDOpInx( self, address ):
        data = self.memory.getData( hex( address ) )
        self.AC = self.ANDOp( self.AC, data )
        return "AND"

    def doASLOpInx( self, address ):
        data = self.memory.getData( hex( address ) )
        data = self.ASLOp( data )
        self.memory.setData( hex( address), data )
        return "ASL"

    def doCMPOpInx( self, address ):
        data = self.memory.getData( hex( address ) )
        data = self.CMPOp( self.AC, data )
        return "CMP"

    def doDECOpInx( self, address ):
        data = self.memory.getData( hex( address ) )
        data = self.SUBOp( data, 1, False )
        self.memory.setData( hex( address), data )
        return "DEC"

    def doEOROpInx( self, address ):
        data = self.memory.getData( hex( address ) )
        self.AC  = self.EOROp( self.AC, data )
        return "EOR"

    def doINCOpInx( self, address ):
        data = self.memory.getData( hex( address ) )
        data = self.ADDOp( data, 1, False )
        self.memory.setData( hex( address), data )
        return "DEC"
    
    def doLDAOpInx( self, address ):
        data = self.memory.getData( hex( address ) )
        self.AC = data
        self.AC = self.doFlags( self.AC )
        return "LDA"

    def doLDXOpInx( self, address ):
        data = self.memory.getData( hex( address ) )
        self.XR = data
        self.XR = self.doFlags( self.XR )
        return "LDX"

    def doLDYOpInx( self, address ):
        data = self.memory.getData( hex( address ) )
        self.YR = data
        self.YR = self.doFlags( self.YR )
        return "LDX"
    
    def doLSROpInx( self, address ):
        data = self.memory.getData( hex( address ) )
        data = self.LSROp( data )
        self.memory.setData( hex( address ), data )
        return "LSR"
    
    def doORAOpInx( self, address ):
        data = self.memory.getData( hex( address ) )
        data = self.OROp( self.AC, data )
        self.memory.setData( hex( address ), data )
        return "ORA"

    def doROLOpInx( self, address ):
        data = self.memory.getData( hex( address ) )
        data = self.ROLOp( data )
        self.memory.setData( hex( address ), data )
        return "ROL"

    def doROROpInx( self, address ):
        data = self.memory.getData( hex( address ) )
        data = self.ROROp( data )
        self.memory.setData( hex( address ), data )
        return "ROR"
    
    def doSBCOpInx( self, address ):
        data = self.memory.getData( hex( address ) )
        self.AC = self.SUBOp( self.AC, data, True )
        self.memory.setData( hex( address ), data )
        return "SBC"
    
    def doSTAOpInx( self, address ):
        self.memory.setData( hex( address), self.AC )
        return "STA"

    def doSTXOpInx( self, address ):
        self.memory.setData( hex( address), self.XR )
        return "STX"

    def doSTYOpInx( self, address ):
        self.memory.setData( hex( address), self.YR )
        return "STY"
    
    
    ######## Arithmetic Ops ########

    def ADDOp( self, val1, val2, addCarry ):
        """
         Adds val1 and val2. If True is specified,
        the carry is added as well, else is it not
        """

        returnVal = self.doSignExtend( val1 ) + self.doSignExtend( val2 ) 
        
        if addCarry:
            self.clearOverflow()

            returnVal += self.SR & self.carry

            self.clearCarry()

            if returnVal < 128 and self.isNegative( val1 ) and self.isNegative( val2 ):
                self.SR |= self.overflow
            
            elif returnVal > 127 and self.isNegative( val1 ) == False and self.isNegative( val2 ) == False:
                self.SR |= self.overflow

            if returnVal & 256:
                self.SR |= self.carry

        returnVal = self.doFlags( returnVal )
        return returnVal
    
    def ANDOp( self, val1, val2 ):
        returnVal = val1 & val2
        returnVal = self.doFlags( returnVal )
        return returnVal
    
    def SUBOp( self, val1, val2, subCarry ):
        """
        Subtracts val2 from val1. If subCarry is specified, 
        the carry bit will be subtracted as well
        """
        returnVal = self.doSignExtend( val1 ) - self.doSignExtend( val2 )
        
        if subCarry:
            self.clearOverflow()
            
            returnVal -=  ( 1 - ( self.SR & self.carry ) )

            self.clearCarry()

            if returnVal > 127 and self.isNegative( val1 ) == False and self.isNegative( val2 ):
                self.SR |= self.overflow
            
            elif returnVal < 128 and self.isNegative( val1 ) and self.isNegative( val2 ) == False:
                self.SR |= self.overflow

            if returnVal & 256:
                self.SR |= self.carry

        returnVal = self.doFlags( returnVal )
        return returnVal
    
    def ASLOp( self, register ):
        temp = ( register & 128 ) >> 7
        register <<= 1
          # Set Carry
        if temp:
            self.SR |= 1
        else:
            self.SR & ~(1)
        
        register = self.doFlags( register )
        return register
    
    def EOROp( self, val1, val2 ):
        returnVal = val1 ^ val2
        returnVal = self.doFlags( returnVal )
        return returnVal
    
    def OROp( self, val1, val2 ):
        returnVal = val1 | val2
        returnVal = self.doFlags( returnVal )
        return returnVal
    
    def LSROp( self, register ):
        temp = register & 1
        register >>= 1

        if temp:
            self.SR |= 1
        else:
            self.SR & ~(1)
        
        register = self.doFlags( register )
        return register
    
    def ROLOp( self, register  ):
        temp = ( 128 & register ) >> 7
        register <<= 1
        register |= ( self.SR & self.carry )
          # This sets the carry, since the carry is in bit 0 of the SR
        if temp:
            self.SR |= 1
        else:
            self.SR &= ~(1)

        register = self.doFlags( register )
        return register
    
    def ROROp( self, register ):
        temp = 1 & register
        register >>= 1
        register |= ( self.SR & self.carry ) << 7
          # This sets the carry, since the carry is in bit 0 of the SR
        if temp:
            self.SR |= 1
        else:
            self.SR &= ~(1)
        register = self.doFlags( register )
        return register
    
    def CMPOp( self, reg1, reg2 ):
        self.clearCarry()
        self.clearNegative()
        self.clearZero()

        reg1 = self.doSignExtend( reg1 )
        reg2 = self.doSignExtend( reg2 )

        if reg1 >= reg2 or reg2 == 0:
            self.SR |= self.carry

        elif self.isNegative( reg1 - reg2 ):
            self.SR |= self.negative

        if reg1 == reg2:
            self.SR |= self.zero
        
    ######## Helper Ops ########

    def doFlags( self, register ):
        self.clearZero()
        self.clearNegative()

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
    
    def getAbsoluteValue( self ):
        """
        Will return the a list containing. value, lowByte, highByte, fullByte
        """
        returnData = []
        self.PC += 1
        lowByte = self.memory.getData( hex( self.PC ) )
        self.PC += 1 
        highByte = self.memory.getData( hex( self.PC ) )
        fullByte = highByte << 8
        fullByte |= lowByte
        val = self.memory.getData( hex( fullByte ) )        
        returnData.append( val )
        returnData.append( lowByte )
        returnData.append( highByte )
        returnData.append( fullByte )
        
        return returnData
    
    # This function was found at https://stackoverflow.com/questions/32030412/twos-complement-sign-extension-python 
    # by Patrick Maupin. It sign extends a value so we can use it when we substract and add without having to do two's
    # complement.
    def doSignExtend( self, value ):
        sign_bit = 1 << ( 8 - 1)
        return (value & (sign_bit - 1)) - (value & sign_bit)
    
    def checkDict( self, num, myDict ):
        if num in myDict.keys():
                return True
        return False
    
    def clearCarry( self ):
        self.SR &= ~( self.carry )
    
    def clearOverflow( self ):
        self.SR &= ~( self.overflow )
    
    def clearNegative( self ):
        self.SR &= ~( self.negative )
    
    def clearZero( self ):
        self.SR &= ~( self.zero )