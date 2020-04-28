import sys
from Memory import Memory
sys.path.append( 'tests/')
from Testing import Testing

# Create the memory object
memory = Memory()

# We have objects file given on the command line.
if len( sys.argv ) > 1:
    if sys.argv[1] == "TESTING.txt":
        Testing( memory )
    else:
        memory.storePrograms( sys.argv[1] )
     
# Infinite loop. 
while True:
    userInput = input("> " )

    if userInput.lower() == "exit":
        quit()
    
    else:
        memory.parseUserInput( userInput )