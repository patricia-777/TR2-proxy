#include <stdio.h>
#include <curl/curl.h>
 // For older cURL versions you will also need 
// #include <curl/types.h>
// #include <curl/easy.h>

#include <string.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main(void) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    char *url = "http://www.cic.com.br/site/wp-content/uploads/2012/06/danilo_forte.jpg";
    char outfilename[FILENAME_MAX] = "file:///Users/patriciagoncalves/Desktop/bbb.jpg";
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        printf("passo1\n");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        printf("passo2\n");
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        printf("passo3\n");
        res = curl_easy_perform(curl);
        printf("passo4\n");
        /* always cleanup */
        curl_easy_cleanup(curl);
        fclose(fp);
    }
    return 0;
}