
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define size 5

struct restaurant
{
	char name[20];
    char type[20];
    char food[20];
    char area[20];
	struct restaurant* next;
};

struct agent
{
	int id;
    char name[20];
    int phone;
    int commission;
    int status;
	struct agent* next;
};

struct user
{
	int id;
    char name[20];
    char address[20];
    int phone;
	struct user* next;
    struct order* right;
};

struct order
{
    char name[20];
    char address[20];
    int phone;
    char menu[20];
    char rest_name[20];
    struct agent* delivery;
    struct order* next;
    time_t t;
};
struct favfood
{
	char food_name[20];
	int count;
};
struct fav_restaurant
{
	char restaurant_name[20];
	int count;
};

struct restaurant *headrestaurant=NULL;
struct agent *headagent=NULL;
struct user *headuser=NULL;
struct order* headorder=NULL;

void addorder(const char name[20],const char address[20],int phone,const char menu[20],const char rest_name[20])
{
    struct order* newnode = (struct order*)malloc(sizeof(struct order));
    strcpy(newnode->name,name);
    strcpy(newnode->address,address);
    newnode->phone=phone;
    strcpy(newnode->menu,menu);
    strcpy(newnode->rest_name,rest_name);
    newnode->next = NULL;
    newnode->t = time(NULL);
    
    struct order* ptr=headorder;
    struct user* p1=headuser;

    struct agent *agentptr=headagent;
    //struct order *start=headorder;
    
    while(agentptr!=NULL && agentptr->status==1 )
    {
        agentptr=agentptr->next;
    }
    
    if(agentptr!=NULL)
    {
        agentptr->status=1;
        newnode->delivery=agentptr;
        printf("\nOrder placed successfully\n");
        printf("Name - %s\n",newnode->name);
        printf("Address - %s\n",newnode->address);
        printf("Phone - %d\n",newnode->phone);
        printf("Menu - %s\n",newnode->menu);
        struct tm* date=localtime(&newnode->t);
        printf("Order placed on %s",asctime(date));
        printf("Delivered by - %s, ID - %d, Phone - %d\n",newnode->delivery->name,newnode->delivery->id,newnode->delivery->phone);


        if(headorder==NULL)
        {
            headorder=newnode;
        }
        else
        {
            ptr =headorder;
            while (ptr->next != NULL)
            {   
                ptr = ptr->next;
            }
            ptr->next = newnode;
            //headorder=start;
        }
        
        //for adding order to user history
        struct order* nnode = (struct order*)malloc(sizeof(struct order));
        strcpy(nnode->name,name);
        strcpy(nnode->menu,menu);
        strcpy(nnode->rest_name,rest_name);
        nnode->t=newnode->t;
        nnode->next=NULL;
        
        while(strcmp(p1->name,name)!=0 && p1!=NULL)
        {
            p1=p1->next;
        }
        
        if(p1->right==NULL)
        {
            p1->right=nnode;
        }
        
        else
        {
            struct order* temp =p1->right;
            while(temp->next != NULL)
            {
                temp=temp->next;
            }
            temp->next=nnode;
        }
    }
    else
    {
        printf("Order not placed no agent available\n");
    }
}

void addnoderestaurant(char w[10],char x[10],char y[10],char z[10])
{
    struct restaurant* start=headrestaurant;
    struct restaurant* newnode = (struct restaurant*)malloc(sizeof(struct restaurant));
    strcpy(newnode->name,w);
    strcpy(newnode->type,x);
    strcpy(newnode->food,y);
    strcpy(newnode->area,z);
    newnode->next = NULL;
  
    if (start == NULL)
    {
        headrestaurant=newnode;
        return;
    }
  
    struct restaurant* ptr = headrestaurant;
    while (ptr->next != NULL)
    {   
        ptr = ptr->next;
    }
    ptr->next = newnode;
  
    headrestaurant=start;
}

void addnodeagent(int w,char x[10],int y,int z)
{
    struct agent* start=headagent;
    struct agent* newnode = (struct agent*)malloc(sizeof(struct agent));

    newnode->id=w;
    strcpy(newnode->name,x);
    newnode->phone=y;
    newnode->commission=z;
    newnode->status=0;
    newnode->next = NULL;
  
    if (start == NULL)
    {
        headagent=newnode;
        return;
    }
  
    struct agent* ptr = start;
    while (ptr->next != NULL)
    {   
        ptr = ptr->next;
    }
    ptr->next = newnode;
  
    headagent=start;
}

void addnodeuser(int w,char x[10],char y[10],int z)
{
    struct user* start=headuser;
    struct user* newnode = (struct user*)malloc(sizeof(struct user));
    newnode->id=w;
    strcpy(newnode->name,x);
    strcpy(newnode->address,y);
    newnode->phone=z;
    newnode->right = NULL;
    newnode->next = NULL;
  
    if (start == NULL)
    {
        headuser=newnode;
        return;
    }
  
    struct user* ptr = headuser;
    while (ptr->next != NULL)
    {   
        ptr = ptr->next;
    }
    ptr->next = newnode;
  
    headuser=start;
}

void searchCategory(char category[])
{
    struct restaurant* head=headrestaurant;
    struct restaurant*ptr=head;
    int status=0;
    while(ptr!=NULL)
    {
        if(strcmp(ptr->type,category)==0)
        {
            status++;
            if(status==1)
            {
                printf("Restaurants found\n");
            }
            printf("%s\n",ptr->name);
        }
        ptr=ptr->next;
    } 
    if(status==0)
    {
        printf("No restaurants found\n");
    }  
}

void searchFood(char Food[])
{
    struct restaurant* head=headrestaurant;
    struct restaurant*ptr=head;
    int status=0;
    while(ptr!=NULL)
    {
        if(strcmp(ptr->food,Food)==0)
        {
            status++;
            if(status==1)
            {
                printf("Restaurants found\n");
            }
            printf("%s\n",ptr->name);
        }
        ptr=ptr->next;
    } 
    if(status==0)
    {
        printf("No restaurants found\n");
    }
}

void searchArea(char Area[])
{
    struct restaurant* head=headrestaurant;
    struct restaurant*ptr=head;
    int status=0;
    while(ptr!=NULL)
    {
        if(strcmp(ptr->area,Area)==0)
        {
            status++;
            if(status==1)
            {
                printf("Restaurants found\n");
            }
            printf("%s\n",ptr->name);
        }
        ptr=ptr->next;
    }   
    if(status==0)
    {
        printf("No restaurants found\n");
    } 
}

void traversalrestaurant()
{
    struct restaurant* ptr=headrestaurant;
	while(ptr!=NULL)
	{	
		printf("%s %s %s %s\n",ptr->name,ptr->type,ptr->food,ptr->area);
		ptr=ptr->next;
	}
}

void traversalagent()
{
    struct agent* ptr=headagent;
	while(ptr!=NULL)
	{	
		printf("%d %s %d %d %d\n",ptr->id,ptr->name,ptr->phone,ptr->commission,ptr->status);
		ptr=ptr->next;
	}
}

void traversaluser()
{
    struct user* ptr=headuser;
	while(ptr!=NULL)
	{	
		printf("%d %s %s %d\n",ptr->id,ptr->name,ptr->address,ptr->phone);
		ptr=ptr->next;
	}
}

void traversalorder()
{
    struct order* newnode=headorder;
    if(newnode==NULL)
    {
        printf("\nNo orders\n");
        return;
    }
    while(newnode!=NULL)
    {
        printf("\nName - %s\n",newnode->name);
        printf("Address - %s\n",newnode->address);
        printf("Phone - %d\n",newnode->phone);
        printf("Menu - %s\n",newnode->menu);
        printf("Delivered by - %s, ID - %d, Phone - %d\n",newnode->delivery->name,newnode->delivery->id,newnode->delivery->phone);
        newnode=newnode->next;
    }
}

void delivery(const char name[],const char addr[],int num,const char food[],int price)
{
    struct order *p1=headorder;
    struct order *p2=NULL;
    while(1)
    {
        if(strcmp(p1->name,name)==0 && strcmp(addr,p1->address)==0 && strcmp(food,p1->menu)==0 && p1->phone==num)
        {
            printf("\nfollowing order is delivered :\n");
            printf("Name - %s\n",p1->name);
            printf("Address - %s\n",p1->address);
            printf("Phone - %d\n",p1->phone);
            printf("Menu - %s\n",p1->menu);
            //struct tm* date=localtime(&newnode->t);//what is tm*
            //printf("Order placed on %s",p1->asctime(date));
            printf("Delivered by - %s, ID - %d, Phone - %d\n",p1->delivery->name,p1->delivery->id,p1->delivery->phone);
            if(p1==headorder)
            {
                headorder=p1->next;
                p1->delivery->status=0;
                (p1->delivery->commission)+=price/10;
                free(p1);
            }
            
            else
            {
                p2->next=p1->next;
                p1->delivery->status=0;
                (p1->delivery->commission)+=price/10;
                free(p1);
            }
            
            break;
        }
        p2=p1;
        p1=p1->next;
    }
}

void cancel(const char name[],const char addr[],int num,const char food[])
{
    struct order *p1=headorder;
    struct order *p2=NULL;
    while(1)
    {
        if(strcmp(p1->name,name)==0 && strcmp(addr,p1->address)==0 && strcmp(food,p1->menu)==0 && p1->phone==num)
        {
            printf("\nfollowing order is cancelled :\n");
            printf("Name - %s\n",p1->name);
            printf("Address - %s\n",p1->address);
            printf("Phone - %d\n",p1->phone);
            printf("Menu - %s\n",p1->menu);
            //struct tm* date=localtime(&newnode->t);//what is tm*
            //printf("Order placed on %s",p1->asctime(date));
            printf("Delivered by - %s, ID - %d, Phone - %d\n",p1->delivery->name,p1->delivery->id,p1->delivery->phone);
            if(p1==headorder)
            {
                headorder=p1->next;
                p1->delivery->status=0;
                free(p1);
            }
            
            else
            {
                p2->next=p1->next;
                p1->delivery->status=0;
                free(p1);
            }
            
            break;
        }
        p2=p1;
        p1=p1->next;
    }
}

void usersdata()
{
    struct user* u1=headuser;
    
    while(u1!=NULL)
    {
        printf("%s ->",u1->name);
        struct order* o1=u1->right;
        while(o1!=NULL)
        {
            printf("%s  ",o1->menu);
            printf("%ld ,",o1->t);
            o1=o1->next;
        }
        printf("\n");
        u1=u1->next;
    }
}

void favouritefooduser(int id)
{
    struct user* u1=headuser;
    time_t temp=time(NULL);
    while(u1->id!=id)
    {
        u1=u1->next;
    }
    
    struct favfood arr[size];
    int i,j;
    for(i=0;i<size;i++)
    {
    	arr[i].count=0;
	}
	
	strcpy(arr[0].food_name,"item1");
	strcpy(arr[1].food_name,"item2");
	strcpy(arr[2].food_name,"item3");
	strcpy(arr[3].food_name,"item4");
	strcpy(arr[4].food_name,"item5");
	
	
	struct order* o1=u1->right;
    while(o1!=NULL)
    {
        if(o1->t >=temp-(180*24*60*60) )
        {
        	i=0;
        	while(strcmp(o1->menu,arr[i].food_name)!=0)
        	{
        		i++;
			}
			arr[i].count++;
		}
        o1=o1->next;
    }
    
    for(i=0;i<size;i++)
    {
    	for(j=i+1;j<size-i-1;j++)
    	{
    		if(arr[i].count<arr[j].count)
    		{
    			struct favfood temp=arr[i];
    			arr[i]=arr[j];
    			arr[j]=temp;
			}
		}
	}
	
	for(i=0;i<3;i++)
	printf(("\n%s %d"),arr[i].food_name,arr[i].count);
	
}

void favourite_restaurant(int n)
{
	struct  fav_restaurant arr[size];
    int i,j;
    for(i=0;i<size;i++)
    {
    	arr[i].count=0;
	}
	
	strcpy(arr[0].restaurant_name,"restaurant1");
	strcpy(arr[1].restaurant_name,"restaurant2");
	strcpy(arr[2].restaurant_name,"restaurant3");
	strcpy(arr[3].restaurant_name,"restaurant4");
	strcpy(arr[4].restaurant_name,"restaurant5");
	
	
    struct user* u1=headuser;
    time_t temp=time(NULL);
    while(u1->next!=NULL)
    {
    	struct order* o1=u1->right;
    	while(o1!=NULL)
    	{
        	if(o1->t >=temp-(n*24*60*60) )
        	{
        		i=0;
        		while(strcmp(o1->rest_name,arr[i].restaurant_name)!=0)
        		{
        			i++;
				}
				arr[i].count++;
			}
        	o1=o1->next;
    	}
        u1=u1->next;
    }
	
	
    for(i=0;i<size;i++)
    {
    	for(j=i+1;j<size-i-1;j++)
    	{
    		if(arr[i].count<arr[j].count)
    		{
    			struct fav_restaurant temp=arr[i];
    			arr[i]=arr[j];
    			arr[j]=temp;
			}
		}
	}
	
	for(i=0;i<3;i++)
	printf(("\n%s %d"),arr[i].restaurant_name,arr[i].count);
	
}

void q7(int n)
{
	struct favfood arr[size];
    int i,j;
    for(i=0;i<size;i++)
    {
    	arr[i].count=0;
	}
	
	strcpy(arr[0].food_name,"item1");
	strcpy(arr[1].food_name,"item2");
	strcpy(arr[2].food_name,"item3");
	strcpy(arr[3].food_name,"item4");
	strcpy(arr[4].food_name,"item5");
	
	
    struct user* u1=headuser;
    time_t temp=time(NULL);
    while(u1->next!=NULL)
    {
    	struct order* o1=u1->right;
    	while(o1!=NULL)
    	{
        	if(o1->t >=temp-(n*24*60*60) )
        	{
        		i=0;
        		while(strcmp(o1->menu,arr[i].food_name)!=0)
        		{
        			i++;
				}
				arr[i].count++;
			}
        	o1=o1->next;
    	}
        u1=u1->next;
    }
	
	
    for(i=0;i<size;i++)
    {
    	for(j=i+1;j<size-i-1;j++)
    	{
    		if(arr[i].count<arr[j].count)
    		{
    			struct favfood temp=arr[i];
    			arr[i]=arr[j];
    			arr[j]=temp;
			}
		}
	}
	
	for(i=0;i<3;i++)
	printf(("\n%s %d"),arr[i].food_name,arr[i].count);
}


int main()
{
	char name[20],type[20],food[20],area[20],address[20];
    int i,id,phone,commission;
    
    FILE * filePointer;

    filePointer = fopen("restaurant.txt","r");
    for(i=0;i<5;i++)
    {
        fscanf(filePointer, "%s %s %s %s",name,type,food,area);
        addnoderestaurant(name,type,food,area);
    }
    fclose(filePointer);

    filePointer = fopen("agent.txt","r");
    for(i=0;i<5;i++)
    {
        fscanf(filePointer, "%d %s %d %d",&id,name,phone,&commission);
        addnodeagent(id,name,phone,commission);
    }
    fclose(filePointer);

    filePointer = fopen("user.txt","r");
    for(i=0;i<5;i++)
    {
        fscanf(filePointer, "%d %s %s %d",&id,name,address,phone);
        addnodeuser(id,name,address,phone);
    }
    fclose(filePointer);
	traversalorder();
    addorder("ef","rcf",452,"item1","restaurant1");
    addorder("bg","ryf",100,"item2","restaurant2");
    addorder("ef","rcf",452,"item2","restaurant2");
    addorder("ef","aaa",152,"item1","restaurant3");
    addorder("dc","ter",400,"item3","restaurant4");
    delivery("ef","rcf",452,"item1",1000);//last parameter is price ->to add agent commission
    cancel("dc","ter",400,"item3");
    usersdata();
    //printf("\nPresent orders:");traversalorder();
    //printf("\nAgent details: \n");traversalagent();
    //favouritefooduser(12);
    //favourite_restaurant(10);
    //q7(10);
    traversalorder();
    return 0;
}
