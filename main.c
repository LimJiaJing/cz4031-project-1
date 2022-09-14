#include <stdio.h>
#include <stdlib.h>

struct Record
{
	char* recordname;
	char* recordavgrating;
	int numofvotes;
};

  int main(void)
{
      struct Record records[10];
      int i=0;
      int loopcounter = 0;
      FILE *fp = fopen("C:/Users/miirf/OneDrive/Desktop/cz4031/data.tsv", "r");
      if(fp == NULL) {
          perror("Unable to open file!");
          exit(1);
      }
     char chunk[128];
    int count= 0;
    int first = 10000;

     while(fgets(chunk, sizeof(chunk), fp) != NULL) {
//         printf("%s",chunk);
        if (first== 10000)
        {
            first = 0;
        }
         struct Record *e = records+i;
         char * token = strtok(chunk, " ");
         while( token != NULL ) {
                if (count ==0)
                {
                    e->recordname = token;

                }
                else if(count ==1)
                {
                    e->recordavgrating = token;
                }
                else{
                    e->numofvotes = (int)token;
                }
      token = strtok(NULL, " ");
   }
   count = 0;
   i+=1;
         loopcounter +=1;
         if (loopcounter == 3)
         {
             break;
         }
     }


    for (i = 0; i < 3; i++) {
       struct Record *e = records+i;  // pointer on ith element
    printf("%s %s %d\n", e->recordname, e->recordavgrating, e->numofvotes);
    }
     fclose(fp);
}

//for (i = 1; i < 11; i++) {
//       printf("okay");
//       struct Record *r = records+i;  // pointer on ith element
//       if (fscanf(fp, "%s %s %d", r->recordname, r->recordavgrating, r->numofvotes) !=10)
//            break;
//    }
//    printf("okay");
//
//    for (i = 1; i < 11; i++) {
//       struct Record *r = records+i;  // pointer on ith element
//    printf("%s %s %d\n", r->recordname, r->recordavgrating, r->numofvotes);
//}
