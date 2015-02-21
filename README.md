# breakMD5
code challenge: find md5 hashed phrase of which an anagram is given

set path to wordlist in line 224

    char path[] = "testlist.txt";

compile with:

    gcc -o breakmd5 breakmd5.c -lcrypto -lssl

## Main resources used:

[http://rosettacode.org/wiki/Permutations#C](http://rosettacode.org/wiki/Permutations#C)  
[http://www.geeksforgeeks.org/print-all-possible-combinations-of-r-elements-in-a-given-array-of-size-n/](http://www.geeksforgeeks.org/print-all-possible-combinations-of-r-elements-in-a-given-array-of-size-n/)  
[https://stackoverflow.com/questions/19173442/reading-each-line-of-file-into-array](https://stackoverflow.com/questions/19173442/reading-each-line-of-file-into-array)  

and more of each of those websites.
