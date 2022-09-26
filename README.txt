Title: SixDegrees


Author: Gabe Smithline 


Time Spent on assignment:
* I spent around 25-30 hours on the assignment, half of my time was spent 
  planning and reading through the code already in the assignment and half 
  was probably spent actually coding.  
Purpose of Program:
* The purpose of this program was to finish implementing the Collabgraph Class 
  and implement the SixDegrees class.  During the assignment I learned 
  about different ways to search a graph, like BFS, DFS, and I got experience 
  interacting with an undirected graph.  
Acknowledgements:
* I would like to acknowledge a few people in helping me with my 
  implementation of the SixDegrees project.  First Professor Allen provided me 
  guidance during my meeting. He gave me some advice on the exclusionary search 
  and after speaking with him it was clear how to do it.  I also would like to 
  acknowledge Igor for answering my questions during office hours.  
  I also would like to acknowledge my use of the tutorialspoint c++ 
  documentation which helped greatly throughout the project.  
File Provided:
* Artist.cpp: This is the implementation of the Artist class that was provided
* Artist.h: Header file of the Artist class provided 
* CollabGraph.cpp: Implementation of the CollabGraph class that was partially 
  implemented by me, but most of the code was provided
* CollabGraph.h: Header file for the CollabGraph class
* main.cpp: driver file of SixDegrees implementation, 
  this is the entry point into the program
* Makefile: This is the makefile to run the program
* SixDegrees.cpp: This is the driver of the SixDegrees implementation, 
  all searches and data is passed through this class 
* SixDegrees.h: Header file for the SixDegrees class 
* TestDriver.cpp: Implementation of the driver file for the test class
* Tests.cpp:  Implementation of the Tests class, 
  this tests the functionality of the program
* Tests.h: Header file for the Tests class
* complete_graph.txt: file to build complete graph for testing scenario
* complete_graph_commands.txt: file to run commands for complete graph
  testing scenario.
* edge_case.txt: file to make graph for edge case testing
* edge_commands.txt: file to run commands to test edge cases
* path_graph.txt: file to build graph that is a path for testing
* path_graph_commands.txt: file to run commands for path graph test
* unconnected_graph.txt: file to build unconnected graph for testing
* unconnected_commands.txt: file to run commands for unconnected graph testing


How to Compile/Run:
* SixDegrees:
   * Run make 
   * ./SixDegrees artists.txt commands.txt (optional) output.txt (optional)
* Tests:
   * Run make tests 
   * ./Tests artists.txt commands.txt output.txt
Description of Data Structures:
* This project was implemented using an undirected graph, 
  and this undirected graph was implemented with an undirected map.  
  The key in said map was the name of the artist and the value was a vertex
  that contained information about the artist and a vector of their edges.  
  A graph is a collection is entially a vertex set and an edge set.  
  Here the vertex set consisted of Vertex structs, 
  each vertex representing an artist.  The edge set consists of Edge structs.  
  An edge here represents a song that two artists collaborated on,
  if they collaborated together they share an edge.  Algorithm wise there were 
  two main ones used for traversals; Breadth First Search and Depth First Search.  
  Breadth First Search, or BFS, will find the shortest path from the start 
  node to the destination node.  It does this using a level order traversal 
  through the graph first evaluating nodes by the distance they are from the 
  start to find the shortest path.  It also utilizes a queue as an 
  auxiliary data structure to run the search, the search runs in O(|V|) + O(|E|) 
  time complexity. Depth First Search, or DFS, just finds any path from 
  the start node to the end node.  Its implementation utilizes a different 
  searching pattern than BFS, it will go in one direction as long as it can 
  then once it cannot go any further it will back track to an unexplored 
  node and explore there.  Its implementation is almost verbatim to BFS, 
  the only difference is really it uses a stack as an auxiliary data structure 
  instead of a queue.  It’s time complexity is the same, O(|V|) + O(|E|). 
Testing:
* Testing wise I tested as I went along diffing my output with the 
  example implementations to make sure they output the same thing.  
  I also created a testing class, in here I wrote tests for the different 
  methods I implemented in the CollabGraph class.  These methods tested the 
  basic functionality of these methods.  Next I wrote one test for the 
  SixDegrees class.  The SixDegrees class has one public method, the method 
  to drive the game, so I had to get creative with how to test the functionality.  
  What I ended up doing was writing one test and creating many different 
  graphs and commands files.  I would test my SixDegrees class against 
  different types of graphs and different types of input to make sure it 
  functioned correctly.  This way I could easily test it over a broad 
  range of scenarios.