This is a priority queue implementation using a binary heap where each level is a linked list. This design improves the efficiency of finding the bottom node or insertion point from (O(n)) to (O(log n)). I think. 

Insertion O(log(n))
Removal O(log(n))

Compile w/:
   g++ HeapWithLinkedListAtHorizontal.cpp -o HeapWithLinkedListAtHorizontal