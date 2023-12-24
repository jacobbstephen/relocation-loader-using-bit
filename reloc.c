#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void convert(char bitMask[4],char maskBits[13]){
    char bin[16][5] = {"0000","0001","0010","0011",
                        "0100","0101","0110","0111",
                        "1000","1001","1010","1011",
                        "1100","1101","1110","1111"
                    };
    strcpy(maskBits,bin[bitMask[0] - (bitMask[0] <= '9' ? '0' : 'A' - 10)]);
    strcat(maskBits,bin[bitMask[1] - (bitMask[1] <= '9' ? '0' : 'A' - 10)]);
    strcat(maskBits,bin[bitMask[2] - (bitMask[2] <= '9' ? '0' : 'A' - 10)]);
    printf("B: %d\n", bitMask[1] - '0');
    
}
void readBitMask(char bitMask[],char line[]){
   
    for(int i = 12, j = 0; i < 15,j < 3; i++,j++){
        bitMask[j] =  line[i];
    }
    bitMask[3] = '\0';
}
void reloc(){   
    char line[100],bitMask[4],maskBits[13],mod[7];
    char addr[7];
    mod[6] = '\0';
    addr[6] = '\0';
    int PROGADDR,starting_addr;
    printf("Enter the Progaddr: ");
    scanf("%x",&PROGADDR);
    FILE* file_ptr = fopen("input.txt","r");
    fseek(file_ptr,0,SEEK_SET);
    fgets(line,sizeof(line),file_ptr);
    strncpy(addr,line+9,6);
    starting_addr = (int) strtol(addr,NULL,16);
    fgets(line,sizeof(line),file_ptr);
    while(line[0] == 'T'){
        strncpy(addr,line+2,6);
        sprintf(addr,"%06X",(int) strtol(addr,NULL,16) - starting_addr +  PROGADDR);
        //readBitMask(bitMask,line);
        strncpy(bitMask,line+12,3);
        printf("%s\n",bitMask);
        convert(bitMask,maskBits);
        for(int i = 16,j = 0; line[i] !='\0';j++,i += 7){
            if(maskBits[j] == '1'){
                strncpy(mod,line+i,6);
                sprintf(mod,"%06X",(int) strtol(mod,NULL,16) - starting_addr +  PROGADDR);
                strncpy(line+i,mod,6);
            }
            printf("[%s]: %c%c\n",addr,line[i],line[i + 1]);
            sprintf(addr,"%06X",(int) strtol(addr,NULL,16) + 1);
            printf("[%s]: %c%c\n",addr,line[i + 2],line[i + 3]);
            sprintf(addr,"%06X",(int) strtol(addr,NULL,16) + 1);
            printf("[%s]: %c%c\n",addr,line[i + 4],line[i +  5]);
            sprintf(addr,"%06X",(int) strtol(addr,NULL,16) + 1);
        }
        fgets(line,sizeof(line),file_ptr);
    }
    fclose(file_ptr);
}
int main(){
    reloc();
    printf("Relocation Completed");;
    return(0);
}