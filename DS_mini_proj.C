#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<ctype.h>
#include<process.h>

static int orders=100;

/*for linked list*/
struct item{
     char name[10];
     int price;
     int orders;
     struct item *next;
};

/*for queue of orders*/
struct queue{
    int orderNo;
    struct queue *next;
};

struct complete{
    int orderNo;
    struct queue *next;
};

struct item *start=NULL;
struct complete *c_start;
struct queue *head=NULL;
struct queue *tail=NULL;

//basic functions
void addItem(char n[],int p);
void enqueue(int orderNo);
int dequeue();    //returns order no.
void addCompleted(int orderNo);

void create();
void menu();
void takeOrder();
void showStatus();
void changeStatus();
//admin functions
void addItem_admin();
void adminStatus();
void adminLogin();
void welcome();

void welcome()
{
    printf("\t\tWELCOME TO SARDAR'S FAST FOOD\t\n");
    printf("\t\tEnter any key to continue: ");
    getch();
}

void addItem(char n[],int p){

	struct item *ptr,*new_item;
	new_item=(struct item *)malloc(sizeof(struct item));
	new_item->price=p;
	strcpy(new_item->name,n);
	new_item->orders=0;
	new_item->next=NULL;

	//traversing
	if(start==NULL){
	start=new_item;
	}else{
	 ptr=start;
	 while(ptr->next!=NULL){
		ptr=ptr->next;
	 }
	ptr->next=new_item;
	}
}

void enqueue(int orderNo){
    struct queue *new_order;
    new_order=(struct queue *)malloc(sizeof(struct queue));
    new_order->orderNo=orderNo;
    new_order->next=NULL;

    if(head==NULL){     //queue is empty
	    head=new_order;
	    tail=head;

    }else{    //only one order is in queue
	    tail->next=new_order;
	    tail= tail->next;
    }
}

int dequeue(){
  struct queue *ptr;

    if(head==NULL){  //queue empty
	return -1;
    }else if(head==tail){    //single element
	  ptr=head;
	  head=NULL;
	  tail=NULL;
    }else{
	ptr=head;
	head=head->next;
    }

    return ptr->orderNo;

}

void addCompleted(int orderNO){
    struct complete *new_complete ;
    new_complete =(struct complete *)malloc(sizeof(struct complete));
    new_complete->orderNo=orderNO;
    new_complete->next=c_start;
    c_start=new_complete;

}

void addItem_admin(){

	char n[10];
	int p;
	printf("enter name of food item\n");
	scanf("%s",&n);
	printf("enter amount\n");
	scanf("%d",&p);
    addItem(n,p);

}

void create(){

	int i=0;
	char name[100];
	char arr_n[100][100]={"pav bhaji  ","aloo paratha  ","chole bhature  ","schezwan noodles  ","dahi kachori   ","malai lassi  ","roti sabzi   ","paneer tikka  ","kaju kismis ice cream","faluda   "};
	int arr_p[]={80,50,60,90,30,40,130,90,60,45};
	for(i=0;i<10;i++){
		strcpy(name,arr_n+i);
		addItem(name,arr_p[i]);
	}
}

void menu(){
	int k=1;
	struct item *ptr;
	ptr=start;
	printf("*********************************************\n");
	printf("sr no.\t   Food Items\t\t price\n");
	printf("*********************************************\n");
	while(ptr!=NULL){

		printf("%d\t   %s\t  %d rs\n\n",k,ptr->name,ptr->price);
		ptr=ptr->next;
		k++;
	}

    takeOrder();
    system("cls");
}

void takeOrder(){
    struct item *FoodItem;
    char again;
    int choice,orderNO;
    FoodItem=start;

    //char again;
    printf("enter food item no.\n");
    scanf("%d",&choice);

    choice--;
    while(choice>0)
    {
	choice--;
	FoodItem=FoodItem->next;

    }
    printf("you selected %s\n",FoodItem->name);
    FoodItem->orders+=1;
    orderNO=orders++;
    printf("your order no is %d\n",orderNO);
    enqueue(orderNO);
}

void showStatus(){
	char c;
    struct queue *ptr;
    ptr=head;
     printf("pending\n");
    while(ptr!=NULL){
	printf("%d\n",ptr->orderNo);
	ptr=ptr->next;
    }
    printf("Completed\n");
    ptr=c_start;
    while(ptr!=NULL){
	printf("%d\n",ptr->orderNo);
	ptr=ptr->next;
    }


}

void adminStatus(){
    struct item *FoodItem;
    int price,orders,total,sale=0;
    char name[10];
    FoodItem=start;


    printf("product\tprice\torders\ttotal\n");
    while(FoodItem!=NULL){
	 strcpy(name,FoodItem->name);
	 price =FoodItem->price;
	 orders=FoodItem->orders;
	 total = price*orders;
	printf("%s\t%d\t%d\t%d\n",name,price,orders,total);
	sale+=total;
	FoodItem=FoodItem->next;
    }
    printf("total sale = %d\n",sale);
}

void adminLogin(){
    char pass[10];
    char password[]="qwerty";
    int result=-1,c;
    int p=0;
    printf("enter password for admin\n");

	do{
		pass[p]=getch();
		if(pass[p]!='\r'){
			printf("*");
		}
		p++;
	}while(pass[p-1]!='\r');
	pass[p-1]='\0';
    result=strcmp(pass,password);
    if(result!=0){
	printf("incorrect password\n");

    }else{
	do{
	    printf("\n\n1.status\t2.add item\t3.change status \t4.logout\n");
	    scanf("%d",&c);
	    switch(c){
		case 1: adminStatus();
		    break;
		case 2: addItem_admin();
		    break;
		case 3: changeStatus();
		    break;

		default:;
	    }
	}while(c!=3);
    }

}

void changeStatus()
{
    int c=0,c1=0,orderNo;
    do {
	printf("press 1 to change status \n 0 to exit ");
	fflush(stdout);
	scanf(" %d",&c);
	if (c==1){
	    orderNo=dequeue();
	    addCompleted(orderNo);
	    printf("order no %d was completed\n",orderNo);
	}else{
	break;
	}
	printf("again? (1/0)");
	fflush(stdout);
	scanf("%d",&c1);
    }while(c1!=0);

}




int main()
{
	int c;
	welcome();
       //system("cls");
       clrscr();
    create();

	do{
		printf("********main menu*********\n\n");
		printf("     1. MENU AND ORDER\n\n     2. ORDER STATUS\n\n     3. ADMIN LOGIN\n\n     4. EXIT\n\n");
		printf("     enter choice\n");
		scanf("%d",&c);
		switch(c)
		{
			case 1: menu();
			break;
			case 2: showStatus();
			break;
			case 3: adminLogin();
			break;

			case 4:break;
		}
	}
	while(c!=4);
    getch();
}
