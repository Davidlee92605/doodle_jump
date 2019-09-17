//elder = 1, nursy = 2, kitty = 3, warrior = 4, apprentice = 5, medicent = 6, deputy = 7, leader = 8
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
 char name[30];
 char occupation[30];
 int age;
 int work;
}Cat;

Cat cat[10000];

int compare_cat(const void *a, const void *b){
 const Cat *catA = (const Cat *) a;
 const Cat *catB = (const Cat *) b;

  if(catA->work == catB->work){
    if(catA->work == 5){
        if(catA->age == catB->age)
        {
            return strcmp(catA->name, catB->name);
        }
        else{
            return (catA->age-catB->age);
        }
  }
    else{
        if(catA->age == catB->age){
            return strcmp(catA->name, catB->name);
        }
        else{
            return (catB->age-catA->age);
        }
    }
 }
 else if(catA->work != catB->work){
        return ((catA->work)-(catB->work));
 }

}


int main(void){
 int num, food;



 while(scanf("%d%d", &num, &food) != EOF){

  for(int i = 0; i < num; i++){
   scanf("%s", &cat[i].name);
   scanf("%s", &cat[i].occupation);
   scanf("%d", &cat[i].age);
  }
  for(int i = 0; i < num; i++){
   if(strcmp(cat[i].occupation, "elder") == 0)cat[i].work = 1;
   if(strcmp(cat[i].occupation, "nursy") == 0)cat[i].work = 2;
   if(strcmp(cat[i].occupation, "kitty") == 0)cat[i].work = 3;
   if(strcmp(cat[i].occupation, "warrior") == 0)cat[i].work = 4;
   if(strcmp(cat[i].occupation, "apprentice") == 0)cat[i].work = 5;
   if(strcmp(cat[i].occupation, "medicent") == 0)cat[i].work = 6;
   if(strcmp(cat[i].occupation, "deputy") == 0)cat[i].work = 7;
   if(strcmp(cat[i].occupation, "leader") == 0)cat[i].work = 8;
  }


  qsort(cat, num, sizeof(Cat), compare_cat);

  for(int i = 0; i < food && i < num; i++){
   printf("%s\n", cat[i].name);
   /*printf("%s ", cat[i].occupation);
   printf("%d ", cat[i].age);
   printf("%d\n", cat[i].work);*/
  }
 }




 return 0;
}
