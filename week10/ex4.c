#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>


struct inode_file{
    int inode;
    char filename[256];
};

int main(int argc, char *argv[]){
    struct inode_file inode_files[1024];
    inode_files[0].inode = 0;
    DIR *dp;
    struct dirent *dirp;
    struct stat filestat;
    char filepath[512];

    dp = opendir("tmp");
    printf("Filename ——— Hard Links\n");
    int n_inodes = 0;
    while ((dirp = readdir(dp)) != NULL) {
        if ( dirp->d_type != 8 ){
            continue;
        }
        int res = snprintf(filepath, sizeof(filepath), "tmp/%s", dirp->d_name);
        if ( res >= 512 || res < 0 ){
            printf("ERROR: write to filepath failed");
            return(1);
        }
        stat(filepath, &filestat);
        if ( filestat.st_nlink >= 2) {
            inode_files[n_inodes].inode = filestat.st_ino;
            strcpy( inode_files[n_inodes].filename, dirp->d_name);
            inode_files[n_inodes + 1].inode = 0;
            n_inodes++;
        }
    }

    int n_inode = 0;
    while ( inode_files[n_inode].inode != 0 ){
        printf("%s ——— ", inode_files[n_inode].filename);
        int inode = inode_files[n_inode].inode;
        int n_inode_inner = 0;
        int amount_printed = 0;
        while ( inode_files[n_inode_inner].inode != 0 ){
            if (inode_files[n_inode_inner].inode == inode){
                if (amount_printed != 0){
                    printf(", ");
                }
                amount_printed++;
                printf("%s", inode_files[n_inode_inner].filename);
            }
            n_inode_inner++;
        }
        n_inode++;
        printf("\n");
    }

    closedir(dp);
    exit(EXIT_SUCCESS);
}
