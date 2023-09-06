#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct items{
    char item[20];
    float price;
    int qty;
};

struct orders{
    char customers[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};  


//functions to generate bills
void generateBillHeader(char name[50],char date[30]){
    printf("\n\n");
        printf("\t   ARORA's Restaurant");
        printf("\n\t  --------------------");
        printf("\nDate:%s",date);
        printf("\nInvoice To: %s",name);
        printf("\n");
        printf("------------------------------------\n");
        printf("Items\t\t");
        printf("QTY\t\t");
        printf("Total\t\t");
        printf("\n-------------------------------------");
        printf("\n\n");
}
void generateBillbody(char item[30],int qty,float price){
    printf("%s\t\t",item);
        printf("%d\t\t",qty);
        printf("%.2f\t\t",qty*price);
        printf("\n");
}

void generateBillFooter(float total){
    printf("\n");
    float dis=0.1*total;
    float netTotal=total-dis;
    float cgst=0.09*netTotal,grandTotal=netTotal + 2*cgst; //nettotal=sgst+cgst
    printf("------------------------------------------\n");
    printf("Sub Total\t\t\t%.2f",total);
    printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
    printf("\n\t\t\t\t--------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nCGST @9%s\t\t\t%.2f","%",cgst);
    printf("\nSGST @9%s\t\t\t%.2f","%",cgst);
    printf("\n----------------------------------------");
    printf("\nGrand Total\t\t\t%.2f",grandTotal);
    printf("\n----------------------------------------\n");
}
int main(){

    int opt,n;
    struct orders ord;
    struct orders order;
    char saveBill='y',contFlag='y';
    char name[50];
    FILE *fp;

    //dashboard
    while(contFlag=='y'){
        system("cls");
        float total=0;
        int invoiceFound=0;
        printf("\t=========ARORA's RESTAURANT============");
        printf("\n\nPlease select your prefered operation:\t");
        printf("\n1.Generate Invoice");
        printf("\n2.Show all Invoices");
        printf("\n3.Search Invoice");
        printf("\n4.Exit");
        printf("\n\nYour choice:\t");
        scanf("%d",&opt);
        fgetc(stdin);
        switch(opt){
            case 1:
            system("cls");
            printf("\nPlease enter the name of the customer:\t");
            
            fgets(ord.customers,50,stdin);
            
            ord.customers[strlen(ord.customers)-1]=0;
            strcpy(ord.date, __DATE__);
            printf("\nPlease enter the number of items:\t");
            scanf("%d",&n);
            ord.numOfItems=n;
            for(int i=0;i<n;i++){
                fgetc(stdin);
                printf("\n\n");
                printf("Please enter the item %d\t",i+1);
                fgets(ord.itm[i].item,20,stdin);
                ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;;
                printf("\nPlease enter the quantity:\t");
                scanf("%d",&ord.itm[i].qty);
                printf("\nPlease enter the unit price:\t");
                scanf("%f",&ord.itm[i].price);
                total += ord.itm[i].qty * ord.itm[i].price;
            }
            generateBillHeader(ord.customers,ord.date);
            for(int i=0;i<ord.numOfItems;i++){
                generateBillbody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
            }
            generateBillFooter(total);
            printf("\nDo you want to save the invoice [y/n]:\t");
            scanf("%s",&saveBill);
            if(saveBill == 'y'){
                fp=fopen("project.txt","ab+");
                int lx=fwrite(&ord,sizeof(struct orders),1,fp);
                if(lx != 0){
                    printf("\nSuccessfully saved");
                }
                else{
                    printf("\nError saving");
                }
                fclose(fp);
            }
            break;
            case 2:
            system("cls");
            fp=fopen("project.txt","rb");
            printf("\n *****Your Previous  Invoices*****\n");
            while(fread(&order,sizeof(struct orders),1,fp)){
                total=0;
                generateBillHeader(order.customers,order.date);
                for(int i=0;i<order.numOfItems;i++){
                    generateBillbody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                    total += order.itm[i].qty * order.itm[i].price;
                }
                generateBillFooter(total);
            }
            fclose(fp);
            break;
            case 3:
            printf("\nEnter the name of the customers:\t");
            
            fgets(name,50,stdin);
            name[strlen(name)-1]=0;
            system("cls");
            fp=fopen("project.txt","rb");
            printf("\t*****Invoice of %s*****\n",name);
            while(fread(&order,sizeof(struct orders),1,fp)){
                total=0;
                if(!strcmp(order.customers,name)){
                    generateBillHeader(order.customers,order.date);
                    for(int i=0;i<order.numOfItems;i++){
                        generateBillbody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                        total += order.itm[i].qty*order.itm[i].price;
                    }
                    generateBillFooter(total);
                    invoiceFound=1;
                }
            }
            if(!invoiceFound){
                printf("Sorry the invoice for %s doesnot exists",name);
            }
            fclose(fp);
            break;
            case 4:
            printf("\n\t\t Thank You! Enjoy your day :)\n\n");
            exit(0);
            default:
            printf("Sorry invalid option");
            break;
        }
        printf("\nDo you want to perform another operation[y/n]:\t");
        scanf("%s", &contFlag);
        system("cls");
    }

}

    

