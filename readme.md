# Radix Tree Server

A radix tree implementation hooked up to a minimal tcp server. This project is
mainly for my own learning but It does have a pretty interesting application.
The radix structure should be very efficient for prefix based queries as well as
being very memory efficient for storing large amounts of similar strings.

> In computer science, a radix tree (also radix trie or compact prefix tree) is a data structure that represents a space-optimized trie in which each node that is the only child is merged with its parent. The result is that the number of children of every internal node is at least the radix r of the radix tree, where r is a positive integer and a power x of 2, having x ≥ 1. Unlike in regular tries, edges can be labeled with sequences of elements as well as single elements. This makes radix trees much more efficient for small sets (especially if the strings are long) and for sets of strings that share long prefixes.
