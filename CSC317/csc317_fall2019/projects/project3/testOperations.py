from RunProgram import RunProgram
from Memory import Memory 


mem = Memory() 
prog = RunProgram( "300R", mem )

# Test SBC
def testSBC_carrySet( ):
    mem.setData( "301", 0xfa )
    prog.AC = 0x10
    prog.SR |= ( prog.carry )
    prog.doSBCOpIm()
    print( "SBC CS: ", end='' )
    if( prog.AC == 22 ):
        print( "PASS" )
    else:
        print( "FAIL: AC =", prog.AC )

def testSBC_carryNotSet( ):
    prog.PC = 0x300
    mem.setData( "301", 0x1 )
    prog.AC = 0x10
    prog.SR &= ~( prog.carry )
    prog.doSBCOpIm()
    print( "SBC CNS: ", end='' )
    if( prog.AC == 14 ):
        print( "PASS" )
    else:
        print( "FAIL: AC =", prog.AC )

def testSignExtend():
    print( "Sign Extend Test:", end=' ' )
    val = prog.doSignExtend( 0xfa )
    val1 = prog.doSignExtend( 0x5 )

    if( val == -6 and val1 == 5 ):
        print( "PASS" )

    else:
        print( "FAIL. val =", val )

def testADDOp( ):
    print( "ADDOp test: ", end = '' )
    val = prog.ADDOp( 0x10, 0xfa, False )
    val1 = prog.ADDOp( 0x10, 0x10, False )

    if( val == 10 and val1 == 32 ):
        print( "PASS" )
    
    else:
        print( "FAIL:", val, val1 )

def testADC( ):
    print( "ADCOp test: ", end = '' )
    prog.SR |= prog.carry
    val = prog.ADDOp( 0x10, 0xfa, True )
    prog.SR |= prog.carry
    val1 = prog.ADDOp( 0x10, 0x10, True )

    if( val == 11 and val1 == 33 ):
        print( "PASS" )
    
    else:
        print( "FAIL:", val, val1 )

def testSUBOp( ):
    print( "SUBOp test: ", end = '' )
    val = prog.SUBOp( 0x10, 0xfa, False )
    val1 = prog.SUBOp( 0x10, 0x10, False )

    if( val == 22 and val1 == 0 ):
        print( "PASS" )
    
    else:
        print( "FAIL:", val, val1 )

def testSBCOp( ):
    print( "SBCOp test: ", end = '' )
    prog.SR |= prog.carry
    val = prog.SUBOp( 0x10, 0xfa, True )
    prog.SR &= ~( prog.carry )
    val1 = prog.SUBOp( 0x10, 0x10, True )

    if( val == 22 and val1 == 0xFF ):
        print( "PASS" )
    
    else:
        print( "FAIL:", val, val1 )

def testCNVFlags1( ):
    print( "CV Flags test 1: ", end='' )
    passed = True
    prog.SR = 0

    prog.ADDOp( 64, 64, True )

    if( prog.SR & prog.carry != 0 ):
         passed = False
    
    if( prog.SR & prog.overflow == 0 ):
        passed = False

    if( prog.SR & prog.negative == 0 ):
        passed = False
    
    if( passed ):
        print( "PASS" )
    
    else:
        print( "FAIL:", prog.SR )

testSBC_carrySet()
testSBC_carryNotSet()
testSignExtend()
testADDOp()
testSUBOp()
testADC()
testSBCOp()
testCNVFlags1()