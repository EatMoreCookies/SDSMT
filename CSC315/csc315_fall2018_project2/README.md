# csc315_fall2018_project2

Tests the theory about the 7 degrees of the actor Kevin Bacon


  The program takes one required argument, the name of a movie database file.
  Each line of this input text file describes a movie, and consists of fields
  separated by the forward slash character (/). The first field is the movie
  name. Remaining fields are the names of the actors/actresses who appeared in
  the movie.
  An adjacency list will be used to represent a weighted graph.
  The graph is used to generate shortest paths from Kevin Bacon to every other
  actor/actress. Unweighted edges will allow a simple breadth-first search (BFS) 
  to find shortest paths. From this a minimum spanning tree (MST) will be
  created from the graph. The MST can be traversed from the start (Kevin Bacon) or
  any other actor/actress, to any other actor/actess, by generating their Bacon
  numbers by counting the number of links between them.
  In addition to computing individual Bacon numbers, the program will perform
  statistical analysis on the graph. After reading in the movie database and
  assigning Bacon numbers, print a histogram of Bacon numbers, the average path
  length (for actors who have been assigned Bacon numbers), and the longest
  shortest paths (actors with the highest Bacon numbers).

