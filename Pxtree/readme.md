# Pxtree
A pxtree is a tree-based data structure for storing a collection of strings. Each node is associated with a character, and a count.  
  
               \0
             /    \
            /      \
          b,0      d,0
           |        |
           |        |
          a,0      a,0
        /  |  \     |
       /   |   \    |
      b,0 n,1 d,1  d,1
       |   |    
       |   |
      y,1 k,1 

The count represents what, and how many, words are present in the tree. E.g. 'bank' is present because there is a 1 next to the last letter, k. 'bab' is not present.  
Examples on how they can be used can be found in main.cpp.
