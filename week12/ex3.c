#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>


int main(int argc, char *argv[]){
    char ch, file_name[100] = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
    struct input_event input[64];
    int fp;
    size_t read_bytes;

    fp = open(file_name, O_RDONLY);

    printf("Available shortcuts:\n\
p+e\nc+a+p\np+s\n");

    if (fp == -1) {
        perror("ERROR: can't open file.\n");
        exit(EXIT_FAILURE);
    }

    int pressed_keys[1024] = {0};

    while(1) { 
        read_bytes = read(fp, input, sizeof(input));
        for(int i = 0; i < (read_bytes/sizeof(struct input_event)); i++) {
            if (input[i].code == 58){
                return 0;
            }
            if (input[i].type == 1 && input[i].value == 1){
                pressed_keys[input[i].code] = 1;
                /* printf("PRESSED: 0x%x (%d)\n", input[i].code, input[i].code); */
            }
            else if (input[i].type == 1 && input[i].value == 0){
                pressed_keys[input[i].code] = 0;
                /* printf("RELEASED: 0x%x (%d)\n", input[i].code, input[i].code); */
            }
        }
        if ( pressed_keys[25] == 1 && pressed_keys[18] == 1 ){
            printf("I passed the Exam!\n");
        }
        else if ( pressed_keys[46] == 1 && pressed_keys[30] == 1 \
                && pressed_keys[25] == 1){
            printf("Get some cappuccino!\n");
        }
        else if ( pressed_keys[25] == 1 && pressed_keys[31] == 1 ){
            printf("Drop :(\n");
        }
    }

    close(fp);
    return 0;
}
