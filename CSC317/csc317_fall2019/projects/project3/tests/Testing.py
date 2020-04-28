from Memory import Memory

class Testing:
    def __init__( self, memory ):
        
        FAILED = 0
        SUCCESS = 0
        linesRead = 0
        with open( "TESTING.txt" ) as file:
            for line in file:
                linesRead += 1
                userInput = line
                memory.parseUserInput( userInput )

                index = userInput.find( ":" )
                inputData  = userInput.split( " " )

                startingAddress = str( userInput[0:index] )
                endingAddress = int( startingAddress, 16 ) + len( inputData ) - 3
                endingAddress = str( hex( endingAddress ) ) 

                userInput2  = startingAddress + "." + endingAddress
                justAString = memory.getMutipleData( userInput2 )
                outPutData = justAString.split( " " )
                
                i = 0
                j = 1
                
                failed = False

                for i in range( 0, len( outPutData ) - 1):
                    if i % 9 != 0 and i != 0:
                        outPutData[i] = outPutData[i].replace( '\n', '')
                        if outPutData[i] != inputData[j] and inputData[j] != '\n':
                            print( "Test on line %d failed " %linesRead )
                            print( outPutData )
                            print( inputData )
                            print( )
                            failed = True
                        
                        j += 1 

                if failed == True:
                    FAILED += 1
                
                else:
                    SUCCESS += 1
                
        print( "# Failed Tests = %d " %FAILED )
        print( "# Successful Tests %d " %SUCCESS )
        print( "Lines Read = %d " %linesRead )
        quit( )
        
        

        
        
        
        
        