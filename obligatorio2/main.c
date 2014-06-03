//
//  main.c
//  obligatorio2
//
//  Created by Alan Gostanian on 02/06/14.
//  Copyright (c) 2014 Alan Gostanian. All rights reserved.
//

#include <stdio.h>
#define W_SIZE 512
int separaPorEspacios(char *s, char out[][W_SIZE]);


int main(int argc, const char * argv[])
{

    // insert code here...
    
    char str[W_SIZE];
    char pval[W_SIZE/2][W_SIZE];

    while (1) {
        if( fgets (str, W_SIZE, stdin)!=NULL ) {
            /* writing content to stdout */
            int words_count = separaPorEspacios(str, pval);
            
            //eval command here
            
            //test words
            for (int i=0; i < words_count; i++) {
                puts(pval[i]);

            }
        }
        
        for (int i=0; i<W_SIZE; i++) {
            str[i] = '\0';
        }
        
        pval[0][0] = '\0';
    }
    

    
    
    return 0;
}

int separaPorEspacios(char *s, char out[][W_SIZE])
{
    int i=0, j=0, k=0;
    
    while (s[i] != '\0') {
        while( s[i] == ' '  || s[i] == '\t')
            i++;
        

        for (j=0; s[i] != ' ' && s[i] != '\t' && j<W_SIZE-1; j++, i++) {
            if (s[i]=='\0') {
                break;
            }
            
            out[k][j] = s[i];
        }
        
        out[k][j+1] = '\0';
        i++;
        k++;
    }
    
    return k;
    
}
