/* permutation and recursion functions adapted from 

http://rosettacode.org/wiki/Permutations#C and 
http://www.geeksforgeeks.org/print-all-possible-combinations-of-r-elements-in-a-given-array-of-size-n/

reading a file into an "array" from

https://stackoverflow.com/questions/19173442/reading-each-line-of-file-into-array
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <wchar.h>
#include <openssl/md5.h>

int i;
char letters[] = "poultry outwits ants";
char md5String[] = "4624d200580677270a54ccff86b9610e";

int compare (const void * a, const void * b) {
  return *(const char *)a - *(const char *)b;
}

int check(char **x, int len)
{
  int i;
  int string_length;
  for (i = 0; i < len; i++){
    if (i == 0){
      string_length = strlen(x[i]);
    } 
    else{
      string_length = string_length + strlen(x[i]);
    }
    string_length = string_length + strlen("  ");
  }
  char string_to_check[string_length * sizeof(char)];
  for (i = 0; i < len; i++){
    if (i == 0){
      strcpy(string_to_check, x[i]);
      strcat(string_to_check, " ");
    }
    else if (i > 0 && i < len - 1){
      strcat(string_to_check, x[i]);
      strcat(string_to_check, " ");
    }
    else{
      strcat(string_to_check, x[i]);
    }
  }
  unsigned char result[MD5_DIGEST_LENGTH];
  
  MD5(string_to_check, strlen(string_to_check), result);
  char result_as_hex[sizeof(md5String)];

  // output
  for(i = 0; i < MD5_DIGEST_LENGTH; i++){
    char temp_hex[12];
    sprintf(temp_hex, "%02x", result[i]);
    if (i == 0){
      strcpy(result_as_hex, temp_hex);
    }
    else{
      strcat(result_as_hex, temp_hex);
    }
  }
  if (strcmp(result_as_hex, md5String) == 0){
    printf("%s\n", string_to_check);
  }
  return 1;
}

char next_lex_perm(char **a, int n) {
# define swap(i, j) {t = a[i]; a[i] = a[j]; a[j] = t;}
  int k, l; 
  char *t;
 
  /* 1. Find the largest index k such that a[k] < a[k + 1]. If no such
        index exists, the permutation is the last permutation. */
  for (k = n - 1; k && a[k - 1] >= a[k]; k--);
  if (!k--) return 0;
 
  /* 2. Find the largest index l such that a[k] < a[l]. Since k + 1 is
     such an index, l is well defined */
  for (l = n - 1; a[l] <= a[k]; l--);
 
  /* 3. Swap a[k] with a[l] */
  swap(k, l);
 
  /* 4. Reverse the sequence from a[k + 1] to the end */
  for (k++, l = n - 1; l > k; l--, k++)
    swap(k, l);
  return 1;
# undef swap
}
 
void perm(char **x, int n, int callback(char **, int))
{
  do {
    if (callback) callback(x, n);
  } while (next_lex_perm(x, n));
}
 
void combinationUtil(char **arr, char **data, int start, int end, int index, int r)
{
  qsort(letters, strlen(letters), 1, compare);
    
    // Current combination is ready to be printed, print it
    if (index == r)
    {
      int current_length = strlen("  ");
      int j;
      for (j=0; j<r; j++){
        current_length = current_length + strlen(data[j]);
      }
      if (current_length == strlen(letters)){                                     
        char valid_anagram[current_length * sizeof(char)]; 
        char *ptr_anagram[r];
        strcpy(valid_anagram, data[0]);                                         
        strcat(valid_anagram, " ");
        ptr_anagram[0] = data[0];                             
        int k;
        for (k=1; k<r; k++){ 
          ptr_anagram[k] = data[k];                                       
          strcat(valid_anagram, data[k]);                             
          if (k < r-1){                                                
            strcat(valid_anagram, " ");                      
          }
        }
        valid_anagram[current_length]='\0';
        current_length = strlen(valid_anagram);
        char anagram_sorted[current_length * sizeof(char)];
        memset(anagram_sorted, '\0', sizeof(anagram_sorted));
        strcpy(anagram_sorted, valid_anagram);

        qsort(anagram_sorted, strlen(anagram_sorted), 1, compare);
        int comparison;
          comparison = strcmp(anagram_sorted, letters);
          if(comparison == 0){
              perm(ptr_anagram, r, check);
          }
        }         
        return;
    }
    // replace index with all possible elements. The condition
    // "end-i+1 >= r-index" makes sure that including one element
    // at index will make a combination with remaining elements
    // at remaining positions
    int i;
    for (i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        combinationUtil((char **)arr, (char **)data, i+1, end, index+1, r);
    }
}

// The main function that prints all combinations of size r
// in arr[] of size n. This function mainly uses combinationUtil()
void printCombination(char **arr, int n, int r)
{
    // A temporary array to store all combination one by one
    char **data[r];
 
    // Print all combination using temprary array 'data[]'
    combinationUtil((char **)arr, (char **)data, 0, n-1, 0, r);
}
 
char ** read_file_into_array(char path[]){
    
  int lines_allocated = 128;
  int max_line_len = 100;

  /* Allocate lines of text */
 char **words = (char **)malloc(sizeof(char*)*lines_allocated);
  if (words==NULL)
  {
    fprintf(stderr,"Out of memory (1).\n");
    exit(1);
  }
  FILE *fp = fopen(path, "r");
  if (fp == NULL)
  {
    fprintf(stderr,"Error opening file.\n");
    exit(2);
  }
  for (i=0;1;i++)
  {
    int j;
    /* Have we gone over our line allocation? */
    if (i >= lines_allocated)
    {
      int new_size;
      /* Double our allocation and re-allocate */
      new_size = lines_allocated*2;
      words = (char **)realloc(words,sizeof(char*)*new_size);
      if (words==NULL)
      {
        fprintf(stderr,"Out of memory.\n");
        exit(3);
      }
      lines_allocated = new_size;
    }
    /* Allocate space for the next line */
    words[i] = malloc(max_line_len);
    if (words[i]==NULL)
    {
      fprintf(stderr,"Out of memory (3).\n");
      exit(4);
    }
    if (fgets(words[i],max_line_len-1,fp)==NULL)
      break;      /* Get rid of CR at end of line */
    for (j=strlen(words[i])-1; j>=0 && (words[i][j]=='\r');j--);
      words[i][j]='\0';
  }
  return words;
}

int main()
{
  qsort(letters, strlen(letters), 1, compare);

  char path[] = "testlist.txt";
  char ** words = read_file_into_array(path);

  // Find character length of words
  int words_length;
  int j;
  for (j = 0; j < i; j++){
    words_length = words_length + strlen(words[j]);
  }
  // Concatenate words
  char* words_concat = (char *)malloc(sizeof(char) * words_length + 1);
  for(j = 0; j < i; j++){    
      strcat(words_concat, words[j]);
  } 
  // Sort words_concat
  qsort(words_concat, strlen(words_concat), 1, compare);
  // Remove duplicate letters
  int words_concat_length = strlen(words_concat);
  for (j=0;j < words_concat_length; j++)
  {
    if (words_concat[j] == words_concat[j+1]){
      memmove(&words_concat[j], &words_concat[j + 1], words_concat_length - j);
      words_concat_length--;
      j--;
    }
    words_concat = (char *)realloc(words_concat,sizeof(char*)*words_concat_length);
  }
  // Remove allowed letters
  for (j=0; j < words_concat_length; j++){
    int k;
    bool flag = false;
    for (k=0; k < strlen(letters); k++){
      if (words_concat[j] == letters[k]){
        memmove(&words_concat[j], &words_concat[j + 1], words_concat_length);
        words_concat_length = words_concat_length -1;
        j--;
        flag = true;
        break;        
      }
    }
    if (flag==true) continue;
    words_concat = realloc(words_concat,sizeof(char*)*words_concat_length);
  }
  
  //printf("%i\n", strlen(words_concat));

  char* c = words_concat;
  /*while (*c) {
    putc(*c++, stdout);
    printf("\n");
  }
  */
  // remove words with disallowed letters
  words_length = i;
  printf("%i\n", words_length);

  for (j=0; j < words_length; j++){
    char* c = words_concat;  
    while(*c){

      if(strchr(words[j], *c)){
        int current_length = strlen(words[j]);
        free((words)[j]);
        (words_length)--;
        int k;
        for(k = j; k <= words_length; k++){
          // Shift elements over to the left by 1 to close the gap
          words[k] = words[k+1];
        }
        j--;      
        break;        
      }
      c++;    
    }
  }
  //for(j = 0; j < words_length; j++)
  //    printf("%s\n", words[j]);
    
  int r = 3;
  int n = words_length;
  printCombination(words, n, r);

  for(;words_length>0;words_length--)
    free(words[words_length]);
  return 0;
}
