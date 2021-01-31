<pre>
<strong>8puzzle and 16puzzle problem solver with IDA* algorithm using manhattan distance</strong>

<strong>Problem:</strong> 
The 8-puzzle problem is a puzzle invented and popularized by Noyes Palmer Chapman in the 1870s.
It is played on a 3-by-3 grid with 8 square blocks labeled 1 through 8 and a blank square.
Your goal is to rearrange the blocks so that they are in order.
You are permitted to slide blocks horizontally or vertically into the blank square.

<strong>Input:</strong>
<ol type="1">
  <li>we insert the size of the puzzle 8 or 15</li>
  <li>insert the starting position of 0 </li>
  <li>insert the remaining elements of the puzzle</li>
</ol>
<strong>example:</strong>
8
3
7 5 4
3 2 1
6 8    //This will initialize the following table which will be solved:

7 5 0
4 3 2
1 6 8
0 is initialize directly from the 2nd argument that we inserted.

</pre>
