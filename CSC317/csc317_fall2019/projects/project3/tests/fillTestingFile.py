import random
file = open( "TESTING.txt", "w+")

for i in range( 0, 1000 ):
    address = hex( random.randint( 0, 65480 ) )
    file.write( str( address ) )
    
    file.write( ": ")
    
    for j in range( 0, random.randint( 0, 64 ) ):
        data = hex( random.randint( 0, 255 ) )
        file.write( str( data ) )
        file.write( " ")
    
    file.write( '\n')


