#include <stdio.h>
#include<string.h>

void computeLPSArray(char* pat, int pat_len, int* lps);
  
// Prints occurrences of txt[] in pat[]
void KMPSearch(char* pat, char* txt) {
  int pat_len = strlen(pat);
  int txt_len= strlen(txt);
  int lps[pat_len];

  computeLPSArray(pat, pat_len, lps);

  int i = 0; // index for txt[]
  int j = 0; // index for pat[]
  while (i < txt_len) {
    if (pat[j] == txt[i]) {
      j++;
      i++;
    }

    if (j == pat_len) {
      printf("Found pattern at index %d. \n", i - j);
      j = lps[j - 1];
    }
    else if (i < txt_len && pat[j] != txt[i]) {
      if (j != 0)
        j = lps[j - 1];
      else
        i = i + 1;
    }
  }
}
  
void computeLPSArray(char* pat, int pat_len, int* lps) {
  // length of the previous longest prefix suffix
  int len = 0;
  lps[0] = 0;

  int now = 1;
  while (now < pat_len) {
    if (pat[now] == pat[len]) {
      len++;
      lps[now] = len;
      now++;
    }
    else {
      if (len != 0) {
        len = lps[len - 1];
      }
      else {
        lps[now] = 0;
        now++;
      }
    }
  }
}
  
int main() {
  // char txt1[] = "ABABDABACDABABCABAB";
  // char pat1[] = "ABABCABAB";
  // KMPSearch(pat1, txt1);

  // char txt2[] = "THIS IS A TEST TEXT";
  // char pat2[] = "TEST";
  // KMPSearch(pat2, txt2);

  char txt3[] = "AABAACAADAABAABA";
  char pat3[] = "AABA";
  KMPSearch(pat3, txt3);

  return 0;
}