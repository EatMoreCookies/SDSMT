import sys
from RabinKarp import RabinKarp

fileName = sys.argv[1]

while True:
    rb = RabinKarp( fileName )
    
    print( "Rabin-Karp String Matching!" )
    print( "Menu:\n1. Find a pattern in the given text document:\n2. Run algorithm with data ouput:\n3. exit:" )
    option = input( "> " )

    if option.strip() == "1":
        phrase = input( "Enter pattern ( case does not matter ): " )

        if len( phrase ) >= 256:
            print( "Phrase too long! Must be < 256." )
        
        else:
            rb.findPatterInFile( phrase )
            rb.printFindings()

    elif option.strip() == "2":
        numTests =  input( "Enter the number of words you would like to run ( < 1000 ): " )
        if( int( numTests ) > 1000 ):
            numTimes = "999"
        rb.testAlgorithm( numTests )
        print( "Look in the testing output file to find the results!\nThe data is in the form of: word,length of word,occurences of word,time it took in secs to find word\n" )

    elif option.strip() == "3":
        quit()

    else:
        print( "Invalid input!\n" )
