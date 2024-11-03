#include <stdio.h>

struct Student{

	int id;
	char name[50];
        float gpa;



};


int main() {
  	int num;

	struct Student student[num];
	printf("Enter the number of students: ");
	scanf("%d",&num);
        for(int i =1;i<=num;i++){
	printf("Enter ID for student %d:",i);
	scanf(" %d",&student[i-1].id);
	printf("Enter name for student %d:",i);
        scanf(" %s",student[i-1].name);
	printf("Enter GPA for student%d:",i);
        scanf(" %f",&student[i-1].gpa);
	
	

	
	}
	for(int i =0;i<num;i++){
	printf("ID: %d, Name: %s, GPA: %f\n", student[i].id, student[i].name, student[i].gpa);
}
    return 0;
}
