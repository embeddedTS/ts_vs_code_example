// Simple Configuration Example for using VS Code for development with 
//  Technologic Systems hardware.
//
// c. 2021 Technologic Systems
//   Michael D. Peters
//
//  This is a slightly more complicated hello world that uses a linked
//  library to demonstrate passing build arguments to the compiler.
//
//  Needs Debian package libssl-dev.

#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <unistd.h>

int main(void)
{
    int i, md_len;
    char hello[] = "Hello World!";
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned char md_value[EVP_MAX_MD_SIZE];

    OpenSSL_add_all_digests();

    md = EVP_get_digestbyname("md5");
    if(!md){ printf("No md5?  Is OpenSSL installed?\n");
        exit(1);
    }

    EVP_MD_CTX_init(mdctx);
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, hello, strlen(hello));
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);

    printf("Hello's MD5 is ");
    for(i = 0; i < md_len; i++) printf("%02x", md_value[i]);
    printf("\n");

    return 0;
}
