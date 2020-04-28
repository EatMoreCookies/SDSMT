import time

class RabinKarp:
    def __init__( self, fileName ):
        self.modValue = 256
        self.constValue = 7
        self.pattern = ""
        self.cols = []
        self.lines = []
        self.fileName = fileName
        
    def __hash__( self, string ):
        hash = 0
        j = 0
        for i in reversed( range( 0, len( string ) ) ):
            hash = ( hash + ord( string[j] ) * self.constValue**i  )
            j += 1

        return hash
    
    def printFindings( self ):
        print( "===================================")
        print( "'" + self.pattern + "'" + " found", len( self.lines ), "times at positions:" )
        
        if len( self.lines ) > 0: 
            for i in range( 0, len( self.lines ) ):
                print( "\tline " + str( self.lines[i] ) + " col " + str( self.cols[i] ) )
        
        print( "===================================\n")

   
    def findPatterInFile( self, pattern ):
        self.openFile()
        
        self.pattern = pattern
        pattern = pattern.lower()

        lines = []
        cols = []
        hashedPattern = self.__hash__( pattern )
        lineNum = 0

        # Main loop in file
        for line in self.file:
            lineNum += 1
            line = line.lower()
            for i in range( 0, len( line ) - len( pattern ) ):
                textHash = self.__hash__( line[ i:i+len( pattern ) ] )
                if textHash == hashedPattern:
                    if pattern == line[i:i+len( pattern ) ]:
                        lines.append( lineNum )
                        cols.append( i + 1 )
        
        self.cols = cols
        self.lines = lines

        self.closeFile()
                
    def testAlgorithm( self, numTests ):
        # LOOK HERE TO TEST #
        num = 0
        testsPassed = 0
        testsFailed = 0
        testTimes = []
        words = open( "testingFile.txt" )
        out = open( "testingOutput.csv", 'w')

        start = time.time()
        
        for i in range( 0, int( numTests ) ):
            num = 0
            word = words.readline()
            word = word.strip()
            word = word.lower()
            
            start = time.time()
            self.findPatterInFile( word )
            end = time.time()
            testTimes.append( end - start )

            self.openFile()
            for line in self.file:
                line = line.lower()
                line = line.strip()
                num += line.count( word )

            self.closeFile()

            out.write( word + "," + str( len(  word )  ) + "," + str( len( self.lines ) ) + "," + str( round( end - start, 5 ) ) + "\n")

            if num == len( self.lines ):
                testsPassed += 1
            else:
                testsFailed += 1
        
        
        words.close()
        out.close()

        print( "\nFor " + str( numTests ) + " tests, " +  str( testsPassed ) + " tests passed and " + str( testsFailed ) + " tests failed." ) 
    
    def closeFile( self ):
        self.file.close()   

    def openFile( self ):
        self.file = open( self.fileName )     