For this project I assumed that the maze files will all be in a .txt file format and there size of the files will not have above
the intiger limit of rows or collumns given, I also assume that all mazes will be given in the same format as the given mazes

The algorithem works in a similar way to the BFS by adding each adjacent spaces that have not been searched and are not walls and looping threw
them giving a direction that was moved to get to the space and marks the space with it. Then when the end if found all loops will end and a reverse 
search is ran to find the path that was taken to find the exit.

To test the algorithem I used diffrent mazes that I made to test different situations all within the assumptions given however I made a bunch of in code error checks
that I feel prevent most possible errors from happening this can be from the file not being found to the maze not having exits or pre defined walls arround the edge.

No special requrements needed to build when using Visual Studio and to run in cmd simpley call it with either a argument with the file path for the maze file
or just the maze file if it is in the same directory as the executable and if none is provided one must be provided inside the program.