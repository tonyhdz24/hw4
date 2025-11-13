# CS 452: Homework #4 : Whack-a-Mole and Race Conditions
## Antonio Hernandez (114225246)
### 1. Code Overview
Overall I found this homework assignment to be a great exercise to understand how threads, locks, and condition variables work. It was nice to be able to directly implement what we've been learning and talking about in class. While, the lectures did a good job at introducing and explaining how threads, locks, and condition variables work being able to work with them directly personally really helped me to truly understand them. For the most part working on this assignment wasn't to bad, I didn't run into any major roadblocks and because it wasn't to complicated I feel that I was able to take my time and read the pthread documentation, and thinks things through.

### 2. How to Run
1. Open a terminal in Onyx
2. cd into the folder containing all relevant files
```bash
cd /path-to-folder/hw4
```
3. Once there compile all the files
```bash
make clean
make
```
4. Then run the Whack-a-Mole simulation
```bash
./wam
```
5. No futher input will be needed and the results of the simulation will be displayed in the terminal
### 3. Results
Here are my results from running the Whack-a-Mole simulation with a capacity of 4 after implementing the multi-threaded queue wrapper
```bash
[tonyhernandez24@onyx hw4]$ ./wam 
(0,0) 2142868 lawnimp_new 
(83,481) 2142870 lawnimp_mole creating
(402,63) 2142874 lawnimp_mole creating
(484,209) 2142871 lawnimp_mole creating
(448,329) 2142879 lawnimp_mole creating
(449,94) 2142875 lawnimp_mole creating
(228,359) 2142878 lawnimp_mole creating
(0,0) 2142869 lawnimp_run 
(105,91) 2142877 lawnimp_mole creating
(566,108) 2142872 lawnimp_mole creating
(15,447) 2142873 lawnimp_mole creating
(431,138) 2142876 lawnimp_mole creating
(402,63) 2142874 lawnimp_mole created
(484,209) 2142871 lawnimp_mole created
(402,63) 2142882 lawnimp_whack whacking
(484,209) 2142885 lawnimp_whack whacking
(448,329) 2142879 lawnimp_mole created
(448,329) 2142880 lawnimp_whack whacking
(228,359) 2142878 lawnimp_mole created
(228,359) 2142889 lawnimp_whack whacking
(566,108) 2142872 lawnimp_mole created
(566,108) 2142884 lawnimp_whack whacking
(484,209) 2142885 lawnimp_whack whacked
(448,329) 2142880 lawnimp_whack whacked
(449,94) 2142875 lawnimp_mole created
(449,94) 2142881 lawnimp_whack whacking
(105,91) 2142877 lawnimp_mole created
(105,91) 2142887 lawnimp_whack whacking
(484,209) 2142885 lawnimp_whack expired
(566,108) 2142884 lawnimp_whack whacked
(83,481) 2142870 lawnimp_mole created
(83,481) 2142886 lawnimp_whack whacking
(228,359) 2142889 lawnimp_whack whacked
(15,447) 2142873 lawnimp_mole created
(15,447) 2142888 lawnimp_whack whacking
(431,138) 2142876 lawnimp_mole created
(431,138) 2142883 lawnimp_whack whacking
(402,63) 2142882 lawnimp_whack whacked
(15,447) 2142888 lawnimp_whack whacked
(449,94) 2142881 lawnimp_whack whacked
(431,138) 2142883 lawnimp_whack whacked
(566,108) 2142884 lawnimp_whack expired
(448,329) 2142880 lawnimp_whack expired
(105,91) 2142887 lawnimp_whack whacked
(431,138) 2142883 lawnimp_whack expired
(402,63) 2142882 lawnimp_whack expired
(105,91) 2142887 lawnimp_whack expired
(83,481) 2142886 lawnimp_whack whacked
(228,359) 2142889 lawnimp_whack expired
(15,447) 2142888 lawnimp_whack expired
(449,94) 2142881 lawnimp_whack expired
(83,481) 2142886 lawnimp_whack expired
```
### 4. Valgrind Results
Below are my Valgrind summary after running ```make valgrind```

```bash
==2144964== LEAK SUMMARY:
==2144964==    definitely lost: 0 bytes in 0 blocks
==2144964==    indirectly lost: 0 bytes in 0 blocks
==2144964==      possibly lost: 0 bytes in 0 blocks
==2144964==    still reachable: 20,708 bytes in 15 blocks
==2144964==         suppressed: 0 bytes in 0 blocks
==2144964== 
==2144964== For lists of detected and suppressed errors, rerun with: -s
==2144964== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
### 5. Sources Used
[Notes provided in class](https://github.com/BoiseState/CS453-resources/tree/master/buff/classes/452/pub)
[Whack-a-Mole Starter Code](https://github.com/BoiseState/CS453-resources/tree/master/buff/classes/452/pub/hw4.vg)
[pthread Documentation](https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread.h.html)