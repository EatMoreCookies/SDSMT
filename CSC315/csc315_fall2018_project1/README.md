# csc315_fall2018_project1.
   1) We will read in the contents of a file in binary, one byte at a time.
   2) Create a histogram using two arrays, one to track the unique character
      and a seperate array of same size to track the frequency of each character
   3) Function call to create a minHeap linked list of structs containing the
      unique character and its frequency count within the input file for future
      compression.
   4) Create a Huffman tree of minHeaps and creating an internal node of frequency
      of the two minNode frequencies added together, where the smallest heapNode
      becomes the leftchild leafNode and the other, the right child leafNode. The
      new internal node will be put back into the minHeap and the process will be
      repeated untile the Huffman tree contains just a single node.
    
   5). From the tree, create a table that stores the characters and their respective
       codes. 
 
   6). Using this table, create a new encoded file from the original. 
 
   7). For the decode, the histogram of the original is stored in the encoded file.
       So, read in the, histogram and re-make the tree to do the decode.
 
   8). Deocode the file by following the bit streams in the tree until a character is
       found.
 
   9) Out put characters to a new file, it should be the same as the original. 
