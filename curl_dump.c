// #include <stdio.h>
// #include <curl/curl.h>
//  // For older cURL versions you will also need 
// // #include <curl/types.h>
// // #include <curl/easy.h>

// #include <string.h>

// size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
//     size_t written = fwrite(ptr, size, nmemb, stream);
//     return written;
// }

// int main(void) {
//     CURL *curl;
//     FILE *fp;
//     CURLcode res;
//     char *url = "http://www.cic.com.br/site/wp-content/uploads/2012/06/danilo_forte.jpg";
//     char outfilename[FILENAME_MAX] = "file:///Users/patriciagoncalves/Desktop/bbb.jpg";
//     curl = curl_easy_init();
//     if (curl) {
//         fp = fopen(outfilename,"wb");
//         curl_easy_setopt(curl, CURLOPT_URL, url);
//         printf("passo1\n");
//         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
//         printf("passo2\n");
//         curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
//         printf("passo3\n");
//         res = curl_easy_perform(curl);
//         printf("passo4\n");
//         /* always cleanup */
//         curl_easy_cleanup(curl);
//         fclose(fp);
//     }
//     return 0;
// }






// #include <stdio.h>
// #include <curl/curl.h>
// int main ()
// {
//   CURL *curl;
//   CURLcode res;
//   curl = curl_easy_init ();
//   if (curl)
//   {
//     curl_easy_setopt (curl, CURLOPT_URL, "http://www.ba.gov.br/");
//     res = curl_easy_perform (curl);
//     curl_easy_cleanup (curl);
//   }
//   return 0;
// }





#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
#include <curl/curl.h>
 
static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}
 
int main(int argc, char *argv[])
{
  CURL *curl_handle;
  static const char *pagefilename = "page.html";
  FILE *pagefile;
 
  if(argc < 2) {
    printf("Usage: %s <URL>\n", argv[0]);
    return 1;
  }
 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* init the curl session */ 
  curl_handle = curl_easy_init();
 
  /* set URL to get here */ 
  curl_easy_setopt(curl_handle, CURLOPT_URL, argv[1]);
 
  /* Switch on full protocol/debug output while testing */ 
  curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);
 
  /* disable progress meter, set to 0L to enable and disable debug output */ 
  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
 
  /* send all data to this function  */ 
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
 
  /* open the file */ 
  pagefile = fopen(pagefilename, "wb");
  if(pagefile) {
 
    /* write the page body to this file handle */ 
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile);
 
    /* get it! */ 
    curl_easy_perform(curl_handle);
 
    /* close the header file */ 
    fclose(pagefile);
  }
 
  /* cleanup curl stuff */ 
  curl_easy_cleanup(curl_handle);
 
  curl_global_cleanup();
 
  return 0;
}


