/********************************************************************
*  NAME: lab2.c
*  BY: Cole Hoener
*  CREATION DATE: 29 Janurary, 2021
*  DESCRIPTION: Given two directories ./a and ./b, passed as parameters to the program, synchronize them, as follows:
*   If a file in a does not exist in directory b, you should replicate it in directory b.
*   If a file in b does not exist in directory a, it should be deleted from directory b.
*   If a file exists in both directories a and b, the file with the most recent modified date / time should be copied from one directory to the other.
*   Prints a log of the program's activities to stdout or stderr.
********************************************************************/

//Declare headers
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

//Declare constants
const int FILE_NAME_SIZE = 128;
const int DIRECTORY_NAME_SIZE = 128;

/*******************************************************************
* NAME :            void copyFiles(source_file, target_file, directA, directB)
*
* DESCRIPTION :     Copies files from directA to directB given the source and target file name
*
* INPUTS :
*       PARAMETERS:
*           char    sourceFile              the name of the source file
*           char    targetFile              the name of the target file
*           char    directA                 the name of directory A
*           char    directB                 the name of directory B
*       
* OUTPUTS :
*       None
*
* PROCESS :
*                   [1]  Copy directory names to temp variables
*                   [2]  Concatanate directory and file names
*                   [3]  Open sources
*                   [4]  Write to target file from source file
*
* NOTES :           
*           Will not throw an error if it cant open files.
* CHANGES :
*/
void copyFiles(char source_file[FILE_NAME_SIZE], char target_file[FILE_NAME_SIZE], char directA[DIRECTORY_NAME_SIZE + FILE_NAME_SIZE], char directB[DIRECTORY_NAME_SIZE + FILE_NAME_SIZE])
{

    //Decalre variables
    char ch;
    FILE *source, *target;
    char directA2[DIRECTORY_NAME_SIZE + FILE_NAME_SIZE];
    char directB2[DIRECTORY_NAME_SIZE + FILE_NAME_SIZE];

    //Need to store parameters to new variables to avoid address manipulation
    strcpy(directA2, directA);
    strcpy(directB2, directB);

    //Appened file to directory path
    strcat(directA2, source_file);
    strcat(directB2, target_file);

    //Open files
    source = fopen(directA2, "r");
    target = fopen(directB2, "w");

    //Copy source file contents to target file contents
    while ((ch = fgetc(source)) != EOF)
        fputc(ch, target);
}

/*******************************************************************
* NAME :            void deleteFilesInB(target_file, directB)
*
* DESCRIPTION :     Deletes target file in directory B
*
* INPUTS :
*       PARAMETERS:
*           char    targetFile              the name of the target file
*           char    directB                 the name of directory B
*       
* OUTPUTS :
*       None
*
* PROCESS :
*                   [1]  Concatanate directory and file name
*                   [2]  Remove file
*
* NOTES :           
*           
* CHANGES :
*/
void deleteFileInB(char target_file[FILE_NAME_SIZE], char directB[DIRECTORY_NAME_SIZE])
{
    //Decalre variables
    char temp[FILE_NAME_SIZE + DIRECTORY_NAME_SIZE];
    FILE *target;

    //Appenedfile to directory path
    strcat(directB, target_file);

    if (remove(directB) == 0)
        printf("Deleted file %s successfully\n", directB);
    else
        printf("Unable to delete the file\n");
}

/*******************************************************************
* NAME :            void checkFiles(totalFilesA, totalFilesB, filesA, filesB, directA, directB)
*
* DESCRIPTION :     Copies files from directA to directB given the source and target file name
*
* INPUTS :
*       PARAMETERS:
*           int     totalFilesA             the total number of files in directory A
*           int     totalFilesB             the total number of files in directory B
*           char    filesA                  the name of the files in directory A
*           char    filesB                  the name of the files in directory B
*           char    directA                 the name of directory A
*           char    directB                 the name of directory B
*       
* OUTPUTS :
*       None
*
* PROCESS :
*                   [1]  Compares filesA and filesB
*                   [2]  Updates files found in both directories with newest version
*                   [3]  Copies files found in directory A that are not found in directory B
*                   [4]  Deletes file in directory B if not found in directory A
*
* NOTES :           
*  
* CHANGES :
*/
void checkFiles(int totalFilesA, int totalFilesB, char filesA[totalFilesA][FILE_NAME_SIZE], char filesB[totalFilesB][FILE_NAME_SIZE], char directA[DIRECTORY_NAME_SIZE], char directB[DIRECTORY_NAME_SIZE])
{
    //Declares variables
    int i;
    int j;
    int totalSame = 0;
    struct stat filestatA;
    struct stat filestatB;
    char pathA[DIRECTORY_NAME_SIZE + FILE_NAME_SIZE];
    char pathB[DIRECTORY_NAME_SIZE + FILE_NAME_SIZE];

    printf("Updating files\n");

    //If a file in A does not exist in B, the file is replicated to B
    //If both files are found, update with newest version
    for (i = 0; i < totalFilesA; i++)
    {
        for (j = 0; j < totalFilesB; j++)
        {
            //Checks if file names are equal
            if (strcmp(filesA[i], filesB[j]) == 0)
            {
                totalSame++;

                //Creates new filepaths to get modifeid time
                strcpy(pathA, directA);
                strcat(pathA, filesA[i]);
                strcpy(pathB, directB);
                strcat(pathB, filesB[j]);

                //Create the time states from file paths and convert them to time
                stat(pathA, &filestatA);
                stat(pathB, &filestatB);
                time_t t1 = (filestatA.st_mtime);
                time_t t2 = (filestatB.st_mtime);

                //Compares modified time and updates older version
                if (t1 - t2 > 0)
                {
                    copyFiles(filesA[i], filesA[i], directA, directB);
                }
                else if (t1 - t2 < 0)
                {
                    copyFiles(filesA[i], filesA[i], directB, directA);
                }
            }
        }

        //If file is not found in directory B
        if (totalSame != 1)
        {
            printf("Copying file %s from directory %s to directory %s\n", filesA[i], directA, directB);
            copyFiles(filesA[i], filesA[i], directA, directB);
        }

        totalSame = 0;
    }

    //If a file in A does not exist in B, the file is replicated to B
    for (i = 0; i < totalFilesB; i++)
    {
        for (j = 0; j < totalFilesA; j++)
        {
            //Checks if file names are equal
            if (strcmp(filesA[j], filesB[i]) == 0)
                totalSame++;
        }

        //If file is not found in directory B
        if (totalSame != 1)
        {
            printf("Removing file %s from directory %s\n", filesB[i], directB);
            deleteFileInB(filesB[i], directB);
        }

        totalSame = 0;
    }
}

/*******************************************************************
* NAME :            int main(argc, **argv)
*
* DESCRIPTION :     Copies files from directA to directB given the source and target file name
*
* INPUTS :
*       PARAMETERS:
*           int     argc                the total number of arguments provided
*           char    argv                the arguments provided
*       
* OUTPUTS :
*       None
*
* PROCESS :
*                   [1]  Check number of arguments
*                   [2]  Makes sure the directories exist and can be opened
*                   [3]  Stores file names from directories in arrays
*                   [4]  Calls checkFiles()
*
* NOTES :           
*  
* CHANGES :
*/
int main(int argc, char **argv)
{
    //Declare variables
    char directA[DIRECTORY_NAME_SIZE];
    char directB[DIRECTORY_NAME_SIZE];
    char *slash = "/";
    DIR *folderA;
    DIR *folderB;
    struct dirent *entry;
    int totalFilesA = -2; //offset of 2 to rid the root directory from total files count
    int totalFilesB = -2; //offset of 2 to rid the root directory from total files count
    int i = 0;

    //Copy arguments to variables
    strcpy(directA, argv[1]);
    strcpy(directB, argv[2]);

    /*
     *Checks that correct number of arguments is provided
    */
    printf("Checking number of arguments...\n\n");
    if (argc < 3)
    {
        printf("Both directories not provided as arguments.\nProgram terminated.\n");
    }
    else if (argc > 3)
    {
        printf("Too many arguments provided.\nProgram terminated.\n");
    }

    /*
     *Opening directories and checking if they exist
     */
    printf("Opening directories...\n\n");
    //Folder A
    folderA = opendir(directA);

    if (folderA == NULL)
    {
        printf("Unable to read directory %s.\n", directA);
        return (1);
    }

    //Folder B
    folderB = opendir(directB);

    if (folderB == NULL)
    {
        printf("Unable to read directory %s.\n", directB);
        return (1);
    }

    /*
     *Reading each file in directory A and storing to an array
    */
    printf("Reading files in directory %s ...\n\n", directA);
    //Counts total files in folderB
    while ((entry = readdir(folderA)))
    {
        totalFilesA++;
    }

    //Creates array of strings to store file names
    char filesA[totalFilesA][FILE_NAME_SIZE];

    //resets loop to fill array
    rewinddir(folderA);

    //Populates array with file names
    while ((entry = readdir(folderA)))
    {
        if (i > 1)
        {
            strcpy(filesA[i - 2], entry->d_name);
        }
        i++;
    }

    /*
     *Reading each file in directory B and storing to an array
    */
    printf("Reading files in directory %s ...\n\n", directB);
    //Counts total files in folderB
    while ((entry = readdir(folderB)))
    {
        totalFilesB++;
    }

    //Creates array of strings to store file names
    char filesB[totalFilesB][FILE_NAME_SIZE];

    //resets loop to fill array
    i = 0;
    rewinddir(folderB);

    //Populates array with file names
    while ((entry = readdir(folderB)))
    {
        if (i > 1)
        {
            strcpy(filesB[i - 2], entry->d_name);
        }
        i++;
    }

    //Addeds to the directory so you can access the contents for later
    strcat(directA, slash);
    strcat(directB, slash);

    //Start of the functions that carry out the soultions
    checkFiles(totalFilesA, totalFilesB, filesA, filesB, directA, directB);

    //Close the directories
    closedir(folderA);
    closedir(folderB);
}