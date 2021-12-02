# A2:
Write program to play a game called A2 (much like BINGO)

## THE IDEA:
 -User executes A2 with a seed (integer) and a Card (a file
  containing a 5x5 matrix of integers). </br>
 -A2.c "calls" (provides) unique random numbers one-by-one. Each time
  a number is called, if that number appears on the user's Card, it
  is "marked". </br>
 -User wins when a row, or column, or all 4 corners, become marked.

## CARD:
 -A Card has 5 columns of 5 numbers each. </br>
 -The number in the middle must ALWAYS be zero (gets marked for free). </br>
  column 1 contains 5 unique integers in [01-15] </br>
  column 2 contains 5 unique integers in [16-30] </br>
  column 3 contains 4 unique integers in [31-45] plus middle integer 00 </br>
  column 4 contains 5 unique integers in [46-60] </br>
  column 5 contains 5 unique integers in [61-75] </br>
 -Card numbers must have exactly 2 digits, and be separated by one space,
  with no extraneous whitespace, not even at the start or end of a line. </br>
 -example of a Card:
 
> cat goodInput

12 23 42 55 74 </br>
04 19 34 46 72 </br>
07 17 00 51 69 </br>
11 30 44 56 62 </br>
09 27 40 47 67 </br>

## A2.c PROGRAM INPUT:
 -User runs A2 with 2 command line arguments: seed and CardFile. </br>
 -The seed is expected to be an integer. </br>
 -The CardFile is expected to be a readable file containing a Card. </br>
 -A correctly-formatted Card would look like the example above. </br>
 -For example, you might run your game as follows, where goodInput
  is the file shown above: </br>
> A2 1063 goodInput

## PLAY THE GAME ALONE:
 -A2 will display the list of unique called numbers so far followed by
  the marked Card (initially, call list is empty and only 00 is marked.) </br>
 -A2 always displays Card with column titles "L", "I", "N", "U", "X". </br>
 -Then, numbers in [01-75] are called until you WIN (which stops program). </br>
 -User triggers the next call by entering any non-enter character. Note
  that input is buffered, so user must hit enter key to get previously-
  typed characters read in, but the enter key itself should not result
  in a separate call. </br>
 -Called numbers are printed with an appropriate prefix of "L", "I", etc.
  e.g., I33.  If that called number is in the Card, the number is
  "marked" on the Card. </br>
 -A2 displays a marked number by printing 'm' after it (no whitespace
  between number and 'm'). </br>
 -Each time user triggers a new call, A2 clears the screen, and displays
  the call list followed by the marked Card. To clear the screen from
  a C program, use:  system("clear"); </br>
 -User may quit A2 at any time, by entering character "q" (any other
  character (except enter) triggers another call). </br>
 -Note that the enter key itself triggers no call. Thus, if user hits
  enter 14 times, no call occurs. When user hits key 'x' (followed by
  enter), only one call occurs. </br>

## PLAY THE GAME WITH OTHERS:
 -2 or more people may play, but they need some extra means of
  communication (so they can coordinate). </br>
 -Each player runs A2 with the SAME SEED, but a different Card. </br>
 -Players coordinate entering characters at the same time. </br>
 -When one player wins, this player must alert the others. </br>
 
 ## WINNING:
 -User wins when their Card has one of these winning conditions: </br>
    all 5 numbers in a column are marked </br>
    all 5 numbers in a row    are marked </br>
    all 4 numbers in the corners are marked </br>
 -When a Card wins, WINNER is printed below the final displayed
  marked Card, and A2 terminates. </br>

## CALLED NUMBERS:
 -Are in [01,75]. </br>
 -Are displayed by A2 with appropriate prefix, e.g., L09 </br>
 -Are unique (no repeats). </br>
 -Are obtained using C's pseudo-random number generator (functions
  srand and rand). </br>
 -If two runs of A2 both use the same seed, both runs will get 
  the SAME stream of random numbers, and thus the same call list. </br>
  
  ## EXIT STATUS:
 -Incorrect seed and/or input file causes A2 to exit before playing
  the game; it sends these messages to STDERR and EXIT with
  these codes: </br>

 -Wrong number of command-line arguments (not 2): </br>
  exit 1. "Usage: A2 seed cardFile"  where "A2" is the name of the
          executing program (thus, would print a different name if
          program were renamed). </br>
 -Invalid seed (first command line argument is not an integer):
  exit 2. "Expected integer seed, but got XX" where "XX" is the
          user-supplied seed (first command line argument).
 -CardFile not readable or doesn't exist: </br>
  exit 3. "XX is nonexistent or unreadable"  where "XX" is the name
          of the user-supplied input file (second command line argument).
 -CardFile has incorrect format: </br>
  exit 4. "XX has bad format"  where "XX" is the name of the
          user-supplied input file (second command line argument). </br>

 -If A2 finishes because user quits prematurely (enters q), or wins:
    exit 0. </br>

## FILES:
    A2.c:       Code containing main and functions it uses
    list.h:     Header file for your List ADT
    list.c:     Code containing your List ADT
    A2Makefile: A makefile to compile your program
