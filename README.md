hugefilesorter
==============

Just a Huge Text File Sorter

BUILD:
make CONF=Release (or Debug)

RUN:
./dist/Release/GNU-Linux-x86/hugefilesorter inputfile outputfile (partsize = 10mB)

DESC:
This project try to optimize memory consumtion for large file content sorting problem. I built this base on the idea of merge sort.

Input file is splited into parts at a predefined size (default is 10mB).
The parts is then sorted by quicksort.
Sorted parts are merged pair by pair. The result of this is a list of new larger parts. The process is repeated until there is only 1 part left which is the output.

This solution requires memory at about 3 times the size of partfile and hardisk space at about 3 time the total size of input file.

TESTED RESULT:
Several tests were taken on a small file (~70 mB) with 10mB part file initial size.
Only 26mB of memory is used in sorting phrase (extra data space is needed for default c++ quick sort) which is the most memory consuming phase.

