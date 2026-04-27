# Reflection Questions

Answer each question in 1-3 sentences. Focus on explaining the concept clearly in your own words. Short, precise answers are better than long, vague ones.

1. **Memory**
    1. What is the difference between memory allocated on the stack and memory allocated on the heap? Give an example of each from this assignment.
        Stack memory is created automatically for local variables and function calls, and it disappears when the function returns. Heap memory is allocated manually with functions like malloc and realloc and stays there until it is freed. In this assignment, local pointers like curr in list functions are on the stack, while Node, Student, and BSTNode objects are on the heap.

    2. Why do we use `Student **arr` instead of `Student *arr` in `insertionSort`? What would happen if we swapped `Student` structs directly instead of swapping pointers?
        We use Student **arr because the array stores pointers to Student structs, not Student structs directly. Swapping pointers is much faster and simpler than copying whole structs. If we swapped full Student structs instead, it would do more copying and be less efficient.

    3. In `cleanup`, why must you use `postorder` traversal rather than `inorder` or `preorder`?
        cleanup must use postorder traversal so it frees the left and right children before freeing the parent. If the parent were freed first, we could lose access to its children and cause memory leaks. Postorder is the safe order for deleting a tree.

    4. Why does `realloc` potentially return a different address than the one you passed in?
        realloc can return a different address because the old block may not have enough room to grow or shrink in place. When that happens, it allocates a new block, copies the data, frees the old block, and returns the new address. That is why we must always use the returned pointer.

2. **Pointers and Structs**
    1. Why do we use `->` to access struct fields through a pointer instead of `.`?
        We use -> when we have a pointer to a struct because it means “dereference the pointer, then access the field.” We use . only when we have the actual struct variable itself. So ptr->value is the pointer version of (*ptr).value.

    2. In the linked list question, why do we save `curr->next` before freeing `curr`?
        We save curr->next before freeing curr because once curr is freed, it is no longer safe to access that memory. If we tried to read curr->next after freeing it, that would be invalid. Saving the next pointer first lets us continue through the list safely.

    3. What is a self-referential struct? How does `Node` differ from `BSTNode`, and why?
        A self-referential struct is a struct that contains a pointer to the same struct type. Node has one self-pointer, next, because a linked list only moves forward one node at a time. BSTNode has two self-pointers, left and right, because a binary search tree can branch in two directions.

3. **Algorithms**
    1. `inorder` traversal of a BST always produces a sorted sequence. Why? How does this connect to `insertionSort`?
        Inorder traversal visits nodes in the order left, root, right. In a BST, smaller names are stored on the left and larger names are stored on the right, so inorder prints the names in sorted order. This connects to insertionSort because both produce the same alphabetical ordering by student name.

    2. How does the left/right decision in `bstInsert` relate to the decision you made in `binarySearch`?
        The left/right decision in bstInsert is based on the same kind of comparison as binarySearch. If the target name comes before the current node’s name, go left; otherwise go right. Both algorithms use ordering to avoid checking everything.

    3. What is the worst case for BST insertion, and when does it occur? What does the tree look like in that case?
        The worst case for BST insertion is O(n). It happens when values are inserted in already sorted or nearly sorted order, so each new node goes only to one side. The tree then becomes skewed and looks like a linked list.

4. **Recursion**
    1. What happens to the call stack when you call `inorder` on a tree of height 5? How many stack frames are active at the deepest point?
        Each recursive call to inorder adds a new stack frame while the function goes deeper into the tree. At the deepest point in a tree of height 5, there are 5 active calls for the nodes on that path. If you also count the final call on NULL, then there would be 6 active frames at that moment.

    2. Why is `binarySearch` easier to implement recursively than iteratively?
        binarySearch is easier to write recursively because each step naturally becomes the same problem on a smaller half of the array. The recursive version matches the algorithm directly. The iterative version works too, but it needs more manual tracking of bounds and loop control.
