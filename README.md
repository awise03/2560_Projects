Project 1: Mastermind
  - Game of Mastermind to be played against the computer.
  - A random n-digit sequence is generated, user must find this sequence
  - Program will return the number of values in the correct poisition and the number of values in the incorrect position.
      - Ex. If code is 1 2 3 4 5 and guess is 5 0 3 2 6, response would be 1, 2 (3 is correct value in correct space, 2 and 5          are correct but in wrong space

Project 2: Flip
  - A game played with a standard deck of 52 cards
  - Player draws the 24 top cards from the deck after shuffling, player can select a card to turnover or end the game
  - Points are assigned based on the following card values:
      - ace = 10 points
      - face card = 5 points
      - 8, 9, 10 = 0 points
      - 7 = points *= 0.5
      - 2, 3, 4, 5, 6 = lose all points
      - heart = +1 point to any thing above

Project 3: Word Search Solver
  -  Given a word search of size n * m, find as many words as possible within the word search
      - Words can be diagonal, up, down, left, right, and can roll over edges
  - Words are found from a provided dictionary file with around 200k words
  - Dictionary file is first sorted using either heap sort, quicksort, or selection sort 

Project 4: Sudoku Solver
  - Recursively sovles a series of provided sudoku puzzles recursively by backtracking when the algorithm reaches a square     
    that can't be filled. 

Project 5: Maze Solver
  - Solves a maze recursively using a DFS or non-recursively using a queue-based BFS.
  - Finds the shortest path for a maze using Dijkstra's algorithm or a BFS algorithm 
