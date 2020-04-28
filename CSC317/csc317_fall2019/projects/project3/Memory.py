import sys
from RunProgram import RunProgram

class Memory:
    def __init__( self ):
        self.MEMORY_SIZE = 65536
        self.USED_MEMORY = 0
        self.memory = bytearray( 2**16 )
    
    # Decide what operation we need to do based off of the user input.
    def parseUserInput( self, userInput ):
        if userInput.find( ":" ) != -1:
            self.storeData( userInput )
        
        elif userInput.find( "R" ) != -1:
            runProgram = RunProgram( userInput, self )
            runProgram.operation()

        elif userInput.find( "." ) != -1:
            print( self.getMutipleData( userInput ) )
        
        # Will just print out that memory location.
        else:
            print( hex( int( userInput, 16 ) ), end=' ' )
            print( hex ( self.getData( userInput ) ) )
            
    # Will store the given data into the correct memory location.
    def storeData( self, userInput ):
        index = userInput.find( ":" )
        userInput = userInput.strip()
        data = userInput.split( " " )
        # Convert Hex string into int address
        address = int( userInput[0:index], 16 )

        for i in range( 1, len( data ) ):
            self.checkMemory( address )
            self.memory[address] = int( data[i], 16  ) 
            self.USED_MEMORY += 1
            address += 1

    def getMutipleData( self, userInput ):
        index = userInput.find( "." )
        # Convert hex string into int address
        startingAddress = int( userInput[ 0:index ], 16 )
        endingAddress = int ( userInput[ index + 1:len( userInput ) ], 16 )

        counter = 0
        data = ""

        while startingAddress <= endingAddress:
            if counter % 8 == 0 or counter == 0:
                if counter != 0:
                    data += '\n'
                data += str( hex( startingAddress ) )
                data += " "
            
            data += str( hex( self.memory[ startingAddress ] ) )
            data += " "
            startingAddress += 1
            counter += 1
            
        return data
    
    def storePrograms( self, fileName ):
        with open( fileName ) as file:
            for line in file:
                fileText = line
                
                if fileText == ":00000001FF":
                    break

                # Start byte of the intel hex code.
                if fileText[0] == ":":
                    self.numProgramBytes = int( fileText[ 1:3 ], 16 )
        
                    # Get address and program record type.          
                    self.programAddress = int( fileText[ 3:7 ], 16 )
                    self.programRecordType = fileText[ 7:9 ]

                    i = 0

                    while i < self.numProgramBytes * 2:
                        data = fileText[i+9:i+11]
                        self.checkMemory( self.programAddress )
                        self.memory[ self.programAddress ] = int( data, 16 )
                        self.USED_MEMORY += 1
                        self.programAddress += 1
                        i += 2
                        
                    self.checkSum = fileText[ i+1:i+3 ] 
            
    def checkMemory( self, index ):
        quitBoolean = False
        
        if self.USED_MEMORY + 1  > self.MEMORY_SIZE:
            print( "ERROR! EXCEEDED MEMORY SIZE!")
            quitBoolean = True

        if index > self.MEMORY_SIZE - 1 or index + 1 <= 0:
            print( "ERROR! MEMORY ADDRESS OUT OF RANGE!" )
            quitBoolean = True

        if quitBoolean == True:
            print( "EXITING NOW..." )
            quit()
    
    def getData( self, address ):
        self.checkMemory( int( address, 16 ) )
        return self.memory[ int( address, 16 ) ]
    
    def setData( self, address, data ):
        self.checkMemory( int( address, 16 ) )
        self.memory[ int( address, 16 ) ] = data 
            



